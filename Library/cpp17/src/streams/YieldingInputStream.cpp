#include "naranja/streams/YieldingInputStream.hpp"


naranja::streams::YieldingInputStream::YieldingInputStream(const std::function<void()>& yield, naranja::streams::IInputStream& inputStream)
    : _yield(yield)
    , _inputStream(inputStream)
{
}

std::size_t naranja::streams::YieldingInputStream::AvailableBytes() const
{
    return _inputStream.AvailableBytes();
}

void naranja::streams::YieldingInputStream::Peek(char* buffer, const std::size_t length)
{
    while (length < _inputStream.AvailableBytes())
    {
        _yield();
    }

    const auto bytesReceived = _inputStream.TryPeek(buffer, length);

    if (bytesReceived != length)
    {
        throw std::logic_error("YieldingInputStream: underlying input stream with invalid TryPeek behaviour.");
    }
}

std::size_t naranja::streams::YieldingInputStream::TryPeek(char *buffer, const std::size_t length)
{
    while(AvailableBytes() == 0)
    {
        _yield();
    }
    return _inputStream.TryPeek(buffer, length);
}

void naranja::streams::YieldingInputStream::Read(char *buffer, const std::size_t length)
{
    auto bytesToReceive = length;
    while (bytesToReceive > 0)
    {
        auto bytesReceived = _inputStream.TryRead(&buffer[length - bytesToReceive], bytesToReceive);
        if (bytesReceived > 0)
        {
            bytesToReceive - bytesReceived;
        }
        else
        {
            _yield();
        }
    }
}

std::size_t naranja::streams::YieldingInputStream::TryRead(char *buffer, const std::size_t length)
{
    while (AvailableBytes() == 0)
    {
        _yield();
    }
    return _inputStream.TryRead(buffer, length);
}

