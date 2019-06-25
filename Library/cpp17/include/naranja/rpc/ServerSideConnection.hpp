#pragma once

#include <boost/asio.hpp>
#include <boost/coroutine2/all.hpp>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/streams/MemoryStream.hpp>
#include <naranja/streams/IBufferedOutputStream.hpp>
#include <naranja/utils/Disposer.hpp>
#include <optional>
#include <vector>

namespace naranja
{
    namespace rpc
    {
        class ObjectBroker;
        class IServerSideService;

        class ServerSideConnection : public std::enable_shared_from_this<ServerSideConnection>, private streams::IBufferedOutputStream
        {
        public:
            static std::shared_ptr<ServerSideConnection> Create(boost::asio::io_service& ioService, const std::shared_ptr<protocol::IProtocol>& protocol)
            {
                return std::shared_ptr<ServerSideConnection>(new ServerSideConnection(ioService, protocol));
            }

            ~ServerSideConnection();

            void Start();
            void Stop();

            void OnDisconnect(const std::function<void()>& disconnectionHandler) { _disconnectionHandler = disconnectionHandler; };

            std::shared_ptr<::naranja::streams::IBufferedOutputStream> ReserveOutputStream();
            
            boost::asio::ip::tcp::socket& Socket() { return _socket; }
            naranja::utils::Disposer RegisterFunctionCallHandler(const protocol::ObjectIdentifier& identifier, const std::function<void(const std::shared_ptr<protocol::IObjectReader>& objectReader, const std::shared_ptr<ServerSideConnection>& connection)>& handler);

        private:
            explicit ServerSideConnection(boost::asio::io_service& ioService, const std::shared_ptr<protocol::IProtocol>& protocol);

            std::mutex _mutex;
            std::mutex _outputStreamReservationMutex;

            std::shared_ptr<protocol::IProtocol> _protocol;
            boost::asio::io_service& _ioService;
            boost::asio::ip::tcp::socket _socket;
            streams::MemoryStream _inputStream;
            std::vector<char> _buffer;
            std::shared_ptr<rpc::ObjectBroker> _broker;
            std::function<void()> _disconnectionHandler;
            
            std::shared_ptr<boost::coroutines2::coroutine<void>::push_type> _processCoroutine;

            void HandleRead();
            void ProcessData();

            std::unordered_map<std::string, std::function<void(const std::shared_ptr<protocol::IObjectReader>& objectReader, const std::shared_ptr<ServerSideConnection>& connection)>> _functionCalls;
            void HandleFunctionCall(const std::shared_ptr<protocol::IObjectReader>& objectReader);

            void Write(const char* buffer, const std::size_t length) override;
            void Flush() override { }
        };
    }
}