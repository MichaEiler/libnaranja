#include "naranja/rpc/ClientSideConnection.hpp"

#include <naranja/core/Exceptions.hpp>
#include <naranja/rpc/IBroker.hpp>
#include <naranja/streams/YieldingInputStream.hpp>
#include <naranja/utils/LockableResource.hpp>
#include <iostream>

#include "SetSocketOptions.hpp"

naranja::rpc::ClientSideConnection::ClientSideConnection(const std::shared_ptr<IBroker>& broker)
    : _buffer(512 * 1024, 0)
    , _service()
    , _socket(_service)
    , _broker(broker)
{

}

void naranja::rpc::ClientSideConnection::Connect(const std::string& serverAddress, const std::uint16_t serverPort)
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
    if (!_processCoroutine)
    {
        _processCoroutine = std::move(boost::coroutines2::coroutine<void>::push_type([this](boost::coroutines2::coroutine<void>::pull_type& yield)
        {
            streams::YieldingInputStream yieldingInputStream([&yield](){ yield(); }, _inputStream);
            utils::LockableResource<streams::IBufferedOutputStream> lockableOutputStream{ std::weak_ptr<streams::IBufferedOutputStream>(shared_from_this()) };

            for (;;)
            {
                _broker->Process(yieldingInputStream, lockableOutputStream);
            }
        }));
    }

    (*_processCoroutine)();
}

