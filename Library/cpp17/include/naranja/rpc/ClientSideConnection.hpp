#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace naranja
{
    namespace rpc
    {
        class ClientSideConnection : public std::enable_shared_from_this<ClientSideConnection>
        {
        public:
            explicit ClientSideConnection();

            void OnConnectionLost(const std::function<void()>& connectionLost) { _connectionLost = connectionLost; }
            void Connect(const std::string& serverAddress, const std::uint16_t serverPort);
            void Write(const char* buffer, const std::size_t length);
            void Close();

        private:
            boost::asio::io_service _service;
            boost::asio::ip::tcp::socket _socket;

            std::vector<char> _buffer;
            std::thread _serviceThread;
            std::function<void()> _connectionLost;

            std::mutex _mutex;

            void HandleRead();
        };
    }
}
