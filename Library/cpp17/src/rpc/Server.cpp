#include "naranja/rpc/Server.hpp"

#include <naranja/rpc/ServerSideConnection.hpp>

naranja::rpc::Server::Server(std::shared_ptr<naranja::protocol::IProtocol> const& protocol, std::uint16_t const port)
    : _protocol(protocol)
    , _service()
    , _acceptor(_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{

}

naranja::rpc::Server::~Server()
{
    Stop();
}

void naranja::rpc::Server::Start()
{
    HandleAccept();
    _serviceThread = std::thread([this](){
        _service.run();
    });
}

void naranja::rpc::Server::Stop()
{
    if (!_service.stopped())
    {
        _service.stop();
    }
    if (_serviceThread.joinable())
    {
        _serviceThread.join();
    }
}

void naranja::rpc::Server::HandleAccept()
{
    auto connection = std::make_shared<ServerSideConnection>(_service);
    auto acceptionHandler = [connection, this](const boost::system::error_code& error){
        if (!error)
        {
            connection->Start();
            _connections.push_back(connection);
        }
        HandleAccept();
    };
    
    _acceptor.async_accept(connection->Socket(), acceptionHandler);//std::bind(acceptionHandler, boost::asio::placeholders::error));
}
