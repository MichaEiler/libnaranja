#include "naranja/streams/MemoryStream.hpp"

naranja::streams::MemoryStream::MemoryStream(const std::size_t cacheSize)
    : _cache(cacheSize, 0)
{

}

std::size_t naranja::streams::MemoryStream::AvailableBytes() const
{
    return _cachedBytes;
}

std::size_t naranja::streams::MemoryStream::TryPeek(char* buffer, const std::size_t length)
{
    if (_cachedBytes == 0)
    {
        return 0;
    }
    
    auto bytesToCopy = std::min(length, std::min(_cachedBytes, _cache.size() - _readPosition));
    std::memcpy(buffer, &_cache[_readPosition], bytesToCopy);

    if (bytesToCopy < length && _cachedBytes > bytesToCopy)
    {
        auto bytesToCopyAtStart = std::min(_cachedBytes - bytesToCopy, length - bytesToCopy);
        std::memcpy(&buffer[bytesToCopy], _cache.data(), bytesToCopyAtStart);
        return bytesToCopy + bytesToCopyAtStart;
    }

    return bytesToCopy;
}

std::size_t naranja::streams::MemoryStream::TryRead(char* buffer, const std::size_t length)
{
    if (_cachedBytes == 0)
    {
        return 0;
    }

    auto bytesToCopy = std::min(length, std::min(_cachedBytes, _cache.size() - _readPosition));
    std::memcpy(buffer, &_cache[_readPosition], bytesToCopy);
    _cachedBytes -= bytesToCopy;
    _readPosition = (_readPosition + bytesToCopy) % _cache.size();

    if (_cachedBytes == 0 || bytesToCopy == length)
    {
        return bytesToCopy;
    }

    auto bytesToCopyAtStart = std::min(_cachedBytes, length - bytesToCopy);
    std::memcpy(buffer + bytesToCopy, _cache.data(), bytesToCopyAtStart);
    _cachedBytes -= bytesToCopyAtStart;
    _readPosition += bytesToCopyAtStart;

    return bytesToCopy + bytesToCopyAtStart;
}

void naranja::streams::MemoryStream::Write(const char* buffer, const std::size_t length)
{
    if (_cache.size() < _cachedBytes + length)
    {
        _cache.resize(std::min(_cachedBytes + length, _cache.size() * 2));
    }

    auto bytesToCopy = std::min(length, _cache.size() - _writePosition);
    std::memcpy(&_cache[_writePosition], buffer, bytesToCopy);
    
    auto bytesToCopyToStart = length - bytesToCopy;
    if (bytesToCopyToStart > 0)
    {
        std::memcpy(&_cache[0], &buffer[bytesToCopy], bytesToCopyToStart);
    }

    _writePosition = (_writePosition + bytesToCopy + bytesToCopyToStart) % _cache.size();
    _cachedBytes += bytesToCopy + bytesToCopyToStart;
}

std::size_t naranja::streams::MemoryStream::Capacity() const
{
    return _cache.size();
}