#include "naranja/rpc/ServerSideConnection.hpp"

#include <naranja/core/Exceptions.hpp>
#include <naranja/rpc/IServerSideService.hpp>
#include <naranja/streams/YieldingInputStream.hpp>

#include "SetSocketOptions.hpp"

naranja::rpc::ServerSideConnection::ServerSideConnection(boost::asio::io_service& ioService, const std::shared_ptr<protocol::IProtocol>& protocol)
    : _protocol(protocol)
    , _ioService(ioService)
    , _socket(ioService)
    , _buffer(512 * 1024)
{
    _processCoroutine.emplace([this](boost::coroutines2::coroutine<void>::pull_type& yield)
    {
        streams::YieldingInputStream yieldingInputStream([&yield](){ yield(); }, _inputStream);
        for (;;)
        {
            const auto nextObject = _protocol->ReadObject(yieldingInputStream);
    
            switch(nextObject->Type())
            {
            case naranja::protocol::ObjectType::FunctionCall:
                HandleFunctionCall(nextObject);
                break;
            case naranja::protocol::ObjectType::FunctionResponse:
                [[fallthrough]];
            case naranja::protocol::ObjectType::Exception:
                throw core::ParseFailureException("The server does not wait for function responses. Invalid object type.");
            default:
                throw core::ParseFailureException("Unknown object type.");
            }
        }
    });
}

naranja::rpc::ServerSideConnection::~ServerSideConnection()
{
    Stop();
}

void naranja::rpc::ServerSideConnection::Start()
{
    SetKeepAlive(_socket);
    HandleRead();
}

void naranja::rpc::ServerSideConnection::Stop()
{
    std::lock_guard<std::mutex> lock(_mutex);

    if (_socket.is_open())
    {
        boost::system::error_code error;
        _socket.close(error);
    }
}

std::shared_ptr<::naranja::streams::IBufferedOutputStream> naranja::rpc::ServerSideConnection::ReserveOutputStream()
{
    struct Wrapper : public ::naranja::streams::IBufferedOutputStream
    {
        std::unique_lock<std::mutex> _lock;
        std::shared_ptr<::naranja::rpc::ServerSideConnection> _connection;

        explicit Wrapper(std::unique_lock<std::mutex>&& lock, const std::shared_ptr<::naranja::rpc::ServerSideConnection>& connection)
            : _lock(std::move(lock))
            , _connection(connection)
        {
        }

        void Write(const char* buffer, const std::size_t length) override { _connection->Write(buffer, length); }
        void Flush() override { _connection->Flush(); }
    };

    std::unique_lock<std::mutex> lock(_outputStreamReservationMutex);
    return std::make_shared<Wrapper>(std::move(lock), shared_from_this());
}

void naranja::rpc::ServerSideConnection::Write(const char* buffer, const std::size_t length)
{
    std::lock_guard<std::mutex> lock(_mutex);

    if (!_socket.is_open())
    {
        throw naranja::core::StreamClosedException();
    }

    boost::system::error_code error;
    boost::asio::write(_socket, boost::asio::buffer(buffer, length), error);

    if (error)
    {
        throw naranja::core::StreamClosedException();
    }
}

void naranja::rpc::ServerSideConnection::HandleRead()
{
    _socket.async_receive(boost::asio::buffer(&_buffer[0], _buffer.size()), 
        [weakConnection = std::weak_ptr<ServerSideConnection>(shared_from_this())](const boost::system::error_code& error, const std::size_t receivedBytes){
            auto connection = weakConnection.lock();
            if (!connection)
            {
                return;
            }

            if (error)
            {
                if (connection->_disconnectionHandler)
                {
                    connection->_disconnectionHandler();
                }

                return;
            }

            if (receivedBytes > 0)
            {
                connection->_inputStream.Write(connection->_buffer.data(), receivedBytes);
                connection->ProcessData();
            }
            connection->HandleRead();
        });
}

void naranja::rpc::ServerSideConnection::ProcessData()
{
    if (*_processCoroutine)
    {
        (*_processCoroutine)();
    }
}

void naranja::rpc::ServerSideConnection::HandleFunctionCall(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    decltype(_functionCalls)::mapped_type handler;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto it = _functionCalls.find(objectReader->Identifier());
        if (it == _functionCalls.end())
        {
            throw core::ParseFailureException("Unknown identifier.");
        }
        handler = it->second;
    }
    handler(objectReader, shared_from_this());
}


naranja::utils::Disposer naranja::rpc::ServerSideConnection::RegisterFunctionCallHandler(const protocol::ObjectIdentifier& identifier, const std::function<void(const std::shared_ptr<protocol::IObjectReader>& objectReader, const std::shared_ptr<ServerSideConnection>& connection)>& handler)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _functionCalls[identifier] = handler;

    return naranja::utils::Disposer([weakConnection = std::weak_ptr<ServerSideConnection>(shared_from_this()), identifier](){
        auto connection = weakConnection.lock();
        if (!connection)
        {
            return;
        }

        std::lock_guard<std::mutex> lock(connection->_mutex);

        auto it = connection->_functionCalls.find(identifier);
        if (it != connection->_functionCalls.end())
        {
            connection->_functionCalls.erase(identifier);
        }
    });
};