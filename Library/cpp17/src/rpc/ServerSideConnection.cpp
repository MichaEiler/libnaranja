#include "naranja/rpc/ServerSideConnection.hpp"

#include <naranja/core/Exceptions.hpp>
#include <boost/bind.hpp>

naranja::rpc::ServerSideConnection::ServerSideConnection(boost::asio::io_service& service)
    : _service(service)
    , _socket(service)
    , _buffer(512 * 1024)
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
            if (!connection || error)
                return;

            //connection->_inputStream.Write(connection->_buffer.data(), receivedBytes);
            //connection->ProcessData();
            // echo test
            connection->Write("received", 8);
            // echo test end
            connection->HandleRead();
        });
}

void naranja::rpc::ServerSideConnection::ProcessData()
{

}

