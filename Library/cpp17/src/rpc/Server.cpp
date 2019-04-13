#include "naranja/rpc/Server.hpp"

using tcp = boost::asio::ip::tcp;

naranja::rpc::Server::Server(std::shared_ptr<naranja::protocol::IProtocol> const& protocol, std::uint16_t const port)
    : _protocol(protocol)
    , _service()
    , _acceptor(_service, tcp::endpoint(tcp::v4(), port))
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

}

void naranja::rpc::Server::HandleAccept()
{

}
