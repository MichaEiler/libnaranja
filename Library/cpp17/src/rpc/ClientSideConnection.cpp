#include "naranja/rpc/ClientSideConnection.hpp"

#include <naranja/core/Exceptions.hpp>
#include <naranja/streams/YieldingInputStream.hpp>

#include "SetSocketOptions.hpp"

naranja::rpc::ClientSideConnection::ClientSideConnection(const std::shared_ptr<protocol::IProtocol>& protocol)
    : _protocol(protocol)
    , _buffer(512 * 1024, 0)
    , _service()
    , _socket(_service)
{
    _processCoroutine.emplace([this](boost::coroutines2::coroutine<void>::pull_type& yield)
    {
        streams::YieldingInputStream yieldingInputStream([&yield]() { yield(); }, _inputStream);

        for (;;) {
            const auto nextObject = _protocol->ReadObject(yieldingInputStream);

            switch (nextObject->Type()) {
                case naranja::protocol::ObjectType::FunctionCall:
                    throw core::ParseFailureException("Clients do not listen for function calls. Invalid object type.");
                case naranja::protocol::ObjectType::FunctionResponse:
                    [[fallthrough]];
                case naranja::protocol::ObjectType::Exception:
                    HandleFunctionResponse(nextObject);
                    break;
                default:
                    throw core::ParseFailureException("Unknown object type.");
            }
        }
    });
}

naranja::rpc::ClientSideConnection::~ClientSideConnection()
{
    if (!_service.stopped())
    {
        Close();
    }
}

void naranja::rpc::ClientSideConnection::Start(const std::string& serverAddress, const std::uint16_t serverPort)
{
    using tcp = boost::asio::ip::tcp;
    tcp::resolver resolver(_service);
    tcp::resolver::query query(serverAddress, std::to_string(serverPort));
    auto endpoints = resolver.resolve(query);

    boost::system::error_code error;
    boost::asio::connect(_socket, endpoints, error);

    SetKeepAlive(_socket);
    
    if (error)
    {
        throw naranja::core::StreamClosedException();
    }

    HandleRead();

    _serviceThread = std::thread([this](){
        _service.run();
    });
}

void naranja::rpc::ClientSideConnection::Close()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (!_service.stopped())
    {
        _socket.close();
        _service.stop();
    }
    if (_serviceThread.joinable())
    {
        _serviceThread.join();
    }
}

std::shared_ptr<::naranja::streams::IBufferedOutputStream> naranja::rpc::ClientSideConnection::ReserveOutputStream()
{
    struct Wrapper : public ::naranja::streams::IBufferedOutputStream
    {
        std::unique_lock<std::mutex> _lock;
        std::shared_ptr<::naranja::rpc::ClientSideConnection> _connection;

        explicit Wrapper(std::unique_lock<std::mutex>&& lock, const std::shared_ptr<::naranja::rpc::ClientSideConnection>& connection)
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

void naranja::rpc::ClientSideConnection::Write(const char* buffer, const std::size_t length)
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

void naranja::rpc::ClientSideConnection::HandleRead()
{
    auto readAction = [weakConnection = std::weak_ptr<ClientSideConnection>(shared_from_this())](const boost::system::error_code& error, const std::size_t receivedBytes){
        auto connection = weakConnection.lock();
        if (!connection)
            return;

        if (error)
        {
            if (connection->_connectionLost)
            {
                connection->_connectionLost();
            }
            return;
        }

        if (receivedBytes > 0)
        {
            connection->_inputStream.Write(connection->_buffer.data(), receivedBytes);
            connection->ProcessData();
        }
        connection->HandleRead();
    };

    _socket.async_receive(boost::asio::buffer(_buffer.data(), _buffer.size()), readAction);
}

void naranja::rpc::ClientSideConnection::ProcessData()
{
    if (*_processCoroutine)
    {
        (*_processCoroutine)();
    }
}

void naranja::rpc::ClientSideConnection::HandleFunctionResponse(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    decltype(_functionResponses)::mapped_type handler;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto it = _functionResponses.find(objectReader->Token());
        if (it == _functionResponses.end())
        {
            throw core::ParseFailureException("No handler registered for received token.");
        }
        handler = it->second;
        _functionResponses.erase(it);
    }
    handler(objectReader);
}

naranja::utils::Disposer naranja::rpc::ClientSideConnection::RegisterFunctionResponseHandler(const protocol::ObjectToken& token, const std::function<void(const std::shared_ptr<protocol::IObjectReader>& objectReader)>& handler)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _functionResponses[token] = handler;

    return naranja::utils::Disposer([weakConnection = std::weak_ptr<ClientSideConnection>(shared_from_this()), token](){
        auto connection = weakConnection.lock();
        if (!connection)
        {
            return;
        }

        std::lock_guard<std::mutex> lock(connection->_mutex);

        auto it = connection->_functionResponses.find(token);
        if (it != connection->_functionResponses.end())
        {
            connection->_functionResponses.erase(token);
        }
    });
}
