#include "naranja/rpc/ServerSideConnection.hpp"

#include <naranja/core/Exceptions.hpp>
#include <naranja/rpc/IService.hpp>
#include <naranja/streams/YieldingInputStream.hpp>
#include <iostream>

naranja::rpc::ServerSideConnection::ServerSideConnection(boost::asio::io_service& ioService, const std::shared_ptr<IService>& service)
    : _ioService(ioService)
    , _socket(ioService)
    , _buffer(512 * 1024)
    , _service(service)
{
    
}

void naranja::rpc::ServerSideConnection::Start()
{
    HandleRead();
}

void naranja::rpc::ServerSideConnection::Stop()
{
    boost::system::error_code error;
    _socket.close(error);
}

void naranja::rpc::ServerSideConnection::Write(const char* buffer, const std::size_t length)
{
    boost::system::error_code error;
    boost::asio::write(_socket, boost::asio::buffer(buffer, length), error);

    if (error)
    {
        // TODO: is this check correct this way?
        throw naranja::exceptions::ConnectionClosed();
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

            connection->_inputStream.Write(connection->_buffer.data(), receivedBytes);
            connection->ProcessData();
            connection->HandleRead();
        });
}

void naranja::rpc::ServerSideConnection::ProcessData()
{
    if (!_processCoroutine)
    {
        _processCoroutine = std::move(boost::coroutines2::coroutine<void>::push_type([this](boost::coroutines2::coroutine<void>::pull_type& yield)
        {
            streams::YieldingInputStream yieldingInputStream([&yield](){ yield(); }, _inputStream);
            for (;;)
            {
                _service->Process(yieldingInputStream, std::dynamic_pointer_cast<streams::IBufferedOutputStream>(shared_from_this()));
            }
        }));
    }

    (*_processCoroutine)();
}

