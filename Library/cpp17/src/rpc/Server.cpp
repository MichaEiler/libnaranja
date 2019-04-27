#include "naranja/rpc/Server.hpp"

#include <future>
#include <naranja/rpc/ServerSideConnection.hpp>
#include <naranja/rpc/IBrokerFactory.hpp>

naranja::rpc::Server::Server(const std::shared_ptr<IBrokerFactory> brokerFactory, const std::uint16_t port)
    : _ioService()
    , _acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    , _brokerFactory(brokerFactory)
{

}

naranja::rpc::Server::~Server()
{
    Stop();
}

void naranja::rpc::Server::Start()
{
    HandleAccept();
    _ioServiceThread = std::thread([this](){
        _ioService.run();
    });
}

void naranja::rpc::Server::Stop()
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
    auto connection = ServerSideConnection::Create(_ioService, _brokerFactory->Create());
    connection->OnDisconnect([weakServer = std::weak_ptr<Server>(shared_from_this()), connection](){
        auto server = weakServer.lock();
        if (!server)
        {
            return;
        }

        server->_ioService.post([connection, server](){
            server->_connections.erase(connection);
        });
    });

    auto acceptionHandler = [connection, this](const boost::system::error_code& error){
        if (!error)
        {
            connection->Start();
            _connections.insert(connection);
        }
        HandleAccept();
    };
    
    _acceptor.async_accept(connection->Socket(), acceptionHandler);
}

std::size_t naranja::rpc::Server::NumberOfConnections()
{
    auto numberOfConnections = std::make_shared<std::promise<std::size_t>>();
    auto future = numberOfConnections->get_future();

    _ioService.post([promise = std::move(numberOfConnections), &connections=_connections]() mutable {
        promise->set_value(connections.size());
    });

    return future.get();
}