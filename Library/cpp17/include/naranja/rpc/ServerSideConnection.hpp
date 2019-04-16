#pragma once

#include <boost/asio.hpp>
#include <boost/coroutine2/all.hpp>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <naranja/streams/AdaptiveMemoryStream.hpp>
#include <naranja/streams/IBufferedOutputStream.hpp>
#include <optional>
#include <vector>

namespace naranja
{
    namespace rpc
    {
        class IService;

        class ServerSideConnection : public std::enable_shared_from_this<ServerSideConnection>, public streams::IBufferedOutputStream
        {
        public:
            static std::shared_ptr<ServerSideConnection> Create(boost::asio::io_service& ioService, const std::shared_ptr<IService>& service)
            {
                return std::shared_ptr<ServerSideConnection>(new ServerSideConnection(ioService, service));
            }

            ~ServerSideConnection();

            void Start();
            void Stop();

            void Write(const char* buffer, const std::size_t length) override;
            void Flush() { }

            void OnDisconnect(const std::function<void()>& disconnectionHandler) { _disconnectionHandler = disconnectionHandler; };

            boost::asio::ip::tcp::socket& Socket() { return _socket; }

        private:
            explicit ServerSideConnection(boost::asio::io_service& ioService, const std::shared_ptr<IService>& service);


            boost::asio::io_service& _ioService;
            boost::asio::ip::tcp::socket _socket;
            streams::AdaptiveMemoryStream _inputStream;
            std::vector<char> _buffer;
            std::shared_ptr<IService> _service;
            std::function<void()> _disconnectionHandler;
            std::mutex _mutex;
            
            std::optional<boost::coroutines2::coroutine<void>::push_type> _processCoroutine;

            void HandleRead();
            void ProcessData();
        };
    }
}