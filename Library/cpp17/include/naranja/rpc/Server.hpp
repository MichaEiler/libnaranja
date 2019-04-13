#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <thread>
#include <vector>

namespace naranja
{
    namespace protocol
    {
        class IProtocol;
    }

    namespace rpc
    {
        class ServerSideConnection;

        class Server final : public std::enable_shared_from_this<Server>
        {
        public:
            explicit Server(std::shared_ptr<protocol::IProtocol> const& protocol, std::uint16_t const port);
            ~Server();

            void Start();
            void Stop();
            
        private:
            boost::asio::io_service _service;
            boost::asio::ip::tcp::acceptor _acceptor;
            std::thread _serviceThread;

            std::shared_ptr<protocol::IProtocol> _protocol;
            std::vector<std::shared_ptr<ServerSideConnection>> _connections;

            void HandleAccept();
        };
    }
}
