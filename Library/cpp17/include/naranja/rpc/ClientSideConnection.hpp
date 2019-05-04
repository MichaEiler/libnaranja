#pragma once

#include <boost/asio.hpp>
#include <boost/coroutine2/all.hpp>
#include <cstdint>
#include <memory>
#include <mutex>
#include <naranja/protocol/IProtocol.hpp>
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
        class ObjectBroker;

        class ClientSideConnection : public std::enable_shared_from_this<ClientSideConnection>, public streams::IBufferedOutputStream
        {
        public:
            static std::shared_ptr<ClientSideConnection> Create(const std::shared_ptr<protocol::IProtocol>& protocol)
            {
                return std::shared_ptr<ClientSideConnection>(new ClientSideConnection(protocol));
            }

            ~ClientSideConnection();

            void OnConnectionLost(const std::function<void()>& connectionLost) { _connectionLost = connectionLost; }

            void Start(const std::string& serverAddress, const std::uint16_t serverPort);
            void Close();

            void Write(const char* buffer, const std::size_t length) override;
            void Flush() override {}

            std::shared_ptr<ObjectBroker> Broker() const { return _broker; }

        private:
            explicit ClientSideConnection(const std::shared_ptr<protocol::IProtocol>& protocol);

            boost::asio::io_service _service;
            boost::asio::ip::tcp::socket _socket;
            streams::MemoryStream _inputStream;
            std::shared_ptr<ObjectBroker> _broker;

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
