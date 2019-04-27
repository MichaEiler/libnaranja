#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <thread>
#include <set>

namespace naranja
{
    namespace protocol
    {
        class IProtocol;
    }

    namespace rpc
    {
        class IBrokerFactory;
        class ServerSideConnection;

        class Server final : public std::enable_shared_from_this<Server>
        {
        public:
            explicit Server(const std::shared_ptr<IBrokerFactory> brokerFactory, const std::uint16_t port);
            ~Server();

            void Start();
            void Stop();

            std::size_t NumberOfConnections();

        private:
            boost::asio::io_service _ioService;
            boost::asio::ip::tcp::acceptor _acceptor;
            std::thread _ioServiceThread;

            std::set<std::shared_ptr<ServerSideConnection>> _connections;
            std::shared_ptr<IBrokerFactory> _brokerFactory;

            void HandleAccept();
        };
    }
}
