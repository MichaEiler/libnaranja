#pragma once

#include <boost/asio.hpp>
#include <boost/coroutine2/all.hpp>
#include <cstdint>
#include <memory>
#include <mutex>
#include <naranja/streams/IBufferedOutputStream.hpp>
#include <naranja/streams/MemoryStream.hpp>
#include <optional>
#include <string>
#include <thread>
#include <vector>

namespace naranja
{
    namespace rpc
    {
        class IBroker;

        class ClientSideConnection : public std::enable_shared_from_this<ClientSideConnection>, public streams::IBufferedOutputStream
        {
        public:
            explicit ClientSideConnection(const std::shared_ptr<IBroker>& broker);

            void OnConnectionLost(const std::function<void()>& connectionLost) { _connectionLost = connectionLost; }
            void Connect(const std::string& serverAddress, const std::uint16_t serverPort);
            void Close();

            void Write(const char* buffer, const std::size_t length) override;
            void Flush() override {}

        private:
            boost::asio::io_service _service;
            boost::asio::ip::tcp::socket _socket;
            streams::MemoryStream _inputStream;
            std::shared_ptr<IBroker> _broker;

            std::vector<char> _buffer;
            std::thread _serviceThread;
            std::function<void()> _connectionLost;

            std::mutex _mutex;

            std::optional<boost::coroutines2::coroutine<void>::push_type> _processCoroutine;

            void HandleRead();
            void ProcessData();
        };
    }
}
