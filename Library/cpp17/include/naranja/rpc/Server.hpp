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
        class ServerSideConnection;
        class IServerSideService;

        class Server final : public std::enable_shared_from_this<Server>
        {
        public:
            static std::shared_ptr<Server> Create(const std::shared_ptr<protocol::IProtocol>& protocol, const std::uint16_t port)
            {
                return std::shared_ptr<Server>(new Server(protocol, port));
            }

            ~Server();

            void RegisterService(const std::shared_ptr<rpc::IServerSideService>& service)
            {
                _services.push_back(service);
            }

            void Start();
            void Close();

            std::size_t NumberOfConnections();

        private:
            explicit Server(const std::shared_ptr<protocol::IProtocol>& protocol, const std::uint16_t port);

            boost::asio::io_service _ioService;
            boost::asio::ip::tcp::acceptor _acceptor;
            std::thread _ioServiceThread;

            std::shared_ptr<protocol::IProtocol> _protocol;
            std::vector<std::shared_ptr<rpc::IServerSideService>> _services;
            std::set<std::shared_ptr<ServerSideConnection>> _connections;

            void HandleAccept();
        };
    }
}
