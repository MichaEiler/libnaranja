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
    , _acceptor()
{
    for (int i = 0; i < 5; ++i)
    {
        try
        {
            _acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
            return;
        } catch(const boost::system::system_error&)
        {
            continue;
        }
    }

    throw std::runtime_error("Failed to bind socket.");
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
    HandleAccept();
    _ioServiceThread = std::thread([this](){
        _ioService.run();
    });
}

void naranja::rpc::Server::Close()
{
    if (!_ioService.stopped())
    {
        _ioService.stop();
    }
    if (_ioServiceThread.joinable())
    {
        _ioServiceThread.join();
    }
    _acceptor->close();
    _connections.clear();
}

void naranja::rpc::Server::HandleAccept()
{
    if (_ioService.stopped())
    {
        return;
    }

    try
    {
        auto connection = ServerSideConnection::Create(_ioService, _protocol);

        connection->OnDisconnect([this, connection](){
            if (!_ioService.stopped())
            {
                _connections.erase(connection);
                //_ioService.post([connection, this](){
                //    _connections.erase(connection);
                //});
            }
        });
        // todo: using shared pointers here might be unsafe
        auto acceptionHandler = [connection, this](const boost::system::error_code& error){
            if (!error)
            {
                connection->Start();
                _connections.insert(connection);
            }

            if (_ioService.stopped())
            {
                return;
            }

            for (auto& service : _services)
            {
                service->RegisterNewConnection(connection);
            }
            
            HandleAccept();
        };
        
        _acceptor->async_accept(connection->Socket(), acceptionHandler);

        }
    catch(const std::bad_weak_ptr&)
    {
        return;
    }
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
