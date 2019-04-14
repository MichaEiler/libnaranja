#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
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

            void Connect(const std::string& serverAddress, const std::uint16_t serverPort);
            void Close();

            void Write(const char* buffer, const std::size_t length);

        private:
            boost::asio::io_service _service;
            boost::asio::ip::tcp::socket _socket;

            std::vector<char> _buffer;
            std::thread _serviceThread;

            void HandleRead();
        };
    }
}
