#include "naranja/rpc/ClientSideConnection.hpp"

#include <naranja/core/Exceptions.hpp>
#include <iostream>

naranja::rpc::ClientSideConnection::ClientSideConnection()
    : _buffer(512 * 1024, 0)
    , _service()
    , _socket(_service)
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

    if (error)
    {
        throw naranja::exceptions::ConnectionClosed();
    }

    HandleRead();

    _serviceThread = std::thread([this](){
        _service.run();
    });
}

void naranja::rpc::ClientSideConnection::Close()
{
    if (!_service.stopped())
    {
        _service.stop();
    }
    if (_serviceThread.joinable())
    {
        _serviceThread.join();
    }
}

void naranja::rpc::ClientSideConnection::Write(const char* buffer, const std::size_t length)
{
    boost::system::error_code error;
    boost::asio::write(_socket, boost::asio::buffer(buffer, length), error);

    if (error)
    {
        throw naranja::exceptions::ConnectionClosed();
    }
}

void naranja::rpc::ClientSideConnection::HandleRead()
{
    auto readAction = [weakConnection = std::weak_ptr<ClientSideConnection>(shared_from_this())](const boost::system::error_code& error, const std::size_t receivedBytes){
        auto connection = weakConnection.lock();
        if (!connection || error)
            return;
        
        // test start
        std::cout.write(connection->_buffer.data(), receivedBytes);
        std::cout << std::endl;
        // test end

        connection->HandleRead();
    };

    _socket.async_receive(boost::asio::buffer(_buffer.data(), _buffer.size()), readAction);
}

