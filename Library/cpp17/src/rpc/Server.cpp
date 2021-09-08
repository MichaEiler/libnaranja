#include "naranja/rpc/Server.hpp"

#include <chrono>
#include <future>
#include <iostream>
#include <naranja/rpc/IServerSideService.hpp>
#include <naranja/rpc/ServerSideConnection.hpp>
#include <thread>

naranja::rpc::Server::Server(const std::shared_ptr<protocol::IProtocol>& protocol, const std::uint16_t port)
    : _ioService()
    , _protocol(protocol)
    , _acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    , _socket(_ioService)
{
}

naranja::rpc::Server::~Server()
{
    if (!_ioService.stopped())
    {
        Close();
    }
}

void naranja::rpc::Server::Start()
{
    _acceptor.listen();
    HandleAccept();
    _ioServiceThread = std::thread([this](){
        _ioService.run();
    });
}

void naranja::rpc::Server::Close()
{
    _acceptor.close();
    if (!_ioService.stopped())
    {
        _ioService.stop();
    }
    if (_ioServiceThread.joinable())
    {
        _ioServiceThread.join();
    }
    _connections.clear();
}

void naranja::rpc::Server::HandleAccept()
{
    auto acceptionHandler = [this](const boost::system::error_code& error){
        if (error || _ioService.stopped())
        {
            return;
        }

        auto connection = ServerSideConnection::Create(_ioService, _protocol, std::move(_socket));
        _socket = boost::asio::ip::tcp::socket(_ioService);

        connection->Start();
        _connections.insert(connection);
        
        connection->OnDisconnect([this, connection](){
            if (!_ioService.stopped())
            {
                _ioService.post([connection, this](){
                    _connections.erase(connection);
                });
            }
        });

        for (auto& service : _services)
        {
            service->RegisterNewConnection(connection);
        }
        
        HandleAccept();
    };
    
    _acceptor.async_accept(_socket, acceptionHandler);
}

std::size_t naranja::rpc::Server::NumberOfConnections()
{
    auto p = std::make_shared<std::promise<std::size_t>>();
    auto future = p->get_future();

    _ioService.post([promise = std::move(p), &connections=_connections]() mutable {
        promise->set_value(connections.size());
    });

    return future.get();
}
