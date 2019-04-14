#pragma once

#include <boost/asio.hpp>
#include <boost/coroutine2/all.hpp>
#include <cstdint>
#include <memory>
#include <naranja/streams/AdaptiveMemoryStream.hpp>
#include <vector>

namespace naranja
{
    namespace rpc
    {
        class ServerSideConnection : public std::enable_shared_from_this<ServerSideConnection>, public streams::IOutputStream
        {
        public:
            explicit ServerSideConnection(boost::asio::io_service& service);

            void Start();
            void Stop();

            void Write(const char* buffer, const std::size_t length) override;

            boost::asio::ip::tcp::socket& Socket() { return _socket; }

        private:
            boost::asio::io_service& _service;
            boost::asio::ip::tcp::socket _socket;
            streams::AdaptiveMemoryStream _inputStream;
            std::vector<char> _buffer;

            void HandleRead();
            void ProcessData();
        };
    }
}