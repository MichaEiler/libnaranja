#pragma once

#include <boost/asio.hpp>
#include <boost/coroutine2/all.hpp>
#include <cstdint>
#include <memory>
#include <mutex>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/streams/IBufferedOutputStream.hpp>
#include <naranja/streams/MemoryStream.hpp>
#include <naranja/utils/Disposer.hpp>
#include <optional>
#include <string>
#include <thread>
#include <vector>

namespace naranja
{
    namespace rpc
    {
        class ClientSideConnection : public std::enable_shared_from_this<ClientSideConnection>, private naranja::streams::IBufferedOutputStream
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

            std::shared_ptr<::naranja::streams::IBufferedOutputStream> ReserveOutputStream();

            naranja::utils::Disposer RegisterFunctionResponseHandler(const protocol::ObjectToken& token, const std::function<void(const std::shared_ptr<protocol::IObjectReader>& objectReader)>& handler);

        private:
            explicit ClientSideConnection(const std::shared_ptr<protocol::IProtocol>& protocol);

            std::mutex _mutex;
            std::mutex _outputStreamReservationMutex;

            std::shared_ptr<protocol::IProtocol> _protocol;
            boost::asio::io_service _service;
            boost::asio::ip::tcp::socket _socket;
            std::vector<char> _buffer;
            std::thread _serviceThread;
            std::function<void()> _connectionLost;
            
            streams::MemoryStream _inputStream;
            std::optional<boost::coroutines2::coroutine<void>::push_type> _processCoroutine;

            std::unordered_map<protocol::ObjectToken, std::function<void(const std::shared_ptr<protocol::IObjectReader>& objectReader)>> _functionResponses;

            void HandleFunctionResponse(const std::shared_ptr<protocol::IObjectReader>& objectReader);
            void HandleRead();
            void ProcessData();

            void Write(const char* buffer, const std::size_t length) override;
            void Flush() override { }
        };
    }
}
