#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <set>
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
        class IBrokerFactory;
        class ServerSideConnection;
        class IServerSideService;

        class Server final : public std::enable_shared_from_this<Server>
        {
        public:
            explicit Server(const std::shared_ptr<IBrokerFactory> brokerFactory, const std::uint16_t port);
            ~Server();

            void RegisterService(const std::shared_ptr<rpc::IServerSideService>& service)
            {
                _services.push_back(service);
            }

            void Start();
            void Stop();

            std::size_t NumberOfConnections();

        private:
            boost::asio::io_service _ioService;
            boost::asio::ip::tcp::acceptor _acceptor;
            std::thread _ioServiceThread;

            std::vector<std::shared_ptr<rpc::IServerSideService>> _services;

            std::set<std::shared_ptr<ServerSideConnection>> _connections;
            std::shared_ptr<IBrokerFactory> _brokerFactory;

            void HandleAccept();
        };
    }
}
