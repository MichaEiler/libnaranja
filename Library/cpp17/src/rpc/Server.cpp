#include "naranja/rpc/Server.hpp"

#include <future>
#include <iostream>
#include <naranja/rpc/IServerSideService.hpp>
#include <naranja/rpc/ServerSideConnection.hpp>

naranja::rpc::Server::Server(const std::shared_ptr<protocol::IProtocol>& protocol, const std::uint16_t port)
    : _ioService()
    , _acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    , _protocol(protocol)
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
    _acceptor.close();
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
        connection->OnDisconnect([weakServer = std::weak_ptr<Server>(shared_from_this()), connection](){
            auto server = weakServer.lock();
            if (!server)
            {
                return;
            }

            if (!server->_ioService.stopped())
            {
                server->_ioService.post([connection, server](){
                    server->_connections.erase(connection);
                });
            }
        });

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
        
        _acceptor.async_accept(connection->Socket(), acceptionHandler);

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
