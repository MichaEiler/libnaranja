#include "naranja/streams/RigidMemoryStream.hpp"

naranja::streams::RigidMemoryStream::RigidMemoryStream(const std::size_t cacheSize)
    : _cache(cacheSize, 0)
{

}

naranja::streams::RigidMemoryStream::~RigidMemoryStream()
{

}

std::size_t naranja::streams::RigidMemoryStream::AvailableBytes() const { return _cachedBytes; }

std::size_t naranja::streams::RigidMemoryStream::TryPeek(char* buffer, const std::size_t length)
{
    std::unique_lock<std::mutex> lock(_cacheMutex);

    while (!_closed && _cachedBytes == 0)
    {
        _cacheCondition.wait_for(lock, std::chrono::milliseconds(1000));
    }

    if (_cachedBytes == 0 && _closed)
    {
        throw naranja::exceptions::StreamClosed();
    }

    const auto bytesToCopy = std::min<std::size_t>(std::min<std::size_t>(length, (_cache.size() - _readPosition)), _cachedBytes);
    std::memcpy(buffer, &_cache[_readPosition], bytesToCopy);

    if (length > bytesToCopy && _cachedBytes > bytesToCopy)
    {
        const auto remainingBytesToCopy = std::min<std::size_t>(length - bytesToCopy, _cachedBytes - bytesToCopy);
        std::memcpy(buffer + bytesToCopy, _cache.data(), remainingBytesToCopy);
        return bytesToCopy + remainingBytesToCopy;
    }

    return bytesToCopy;
}

std::size_t naranja::streams::RigidMemoryStream::TryRead(char* buffer, const std::size_t length)
{
    std::unique_lock<std::mutex> lock(_cacheMutex);

    while (!_closed && _cachedBytes == 0)
    {
        _cacheCondition.wait_for(lock, std::chrono::milliseconds(1000));
    }

    if (_cachedBytes == 0 && _closed)
    {
        throw naranja::exceptions::StreamClosed();
    }

    const auto previousCachedBytes = _cachedBytes;

    const auto bytesToCopy = std::min<std::size_t>(std::min<std::size_t>(length, (_cache.size() - _readPosition)), _cachedBytes);
    std::memcpy(buffer, &_cache[_readPosition], bytesToCopy);
    _cachedBytes -= bytesToCopy;
    _readPosition = (_readPosition + bytesToCopy) % _cache.size();

    if (length > bytesToCopy && _cachedBytes > 0)
    {
        const auto remainingBytesToCopy = std::min<std::size_t>(length - bytesToCopy, _cachedBytes);
        std::memcpy(buffer + bytesToCopy, _cache.data(), remainingBytesToCopy);
        _cachedBytes -= remainingBytesToCopy;
        _readPosition = (_readPosition + remainingBytesToCopy) % _cache.size();
    }

    _cacheCondition.notify_one();

    return previousCachedBytes - _cachedBytes;
}

void naranja::streams::RigidMemoryStream::Write(const char* buffer, const std::size_t length)
{
    std::unique_lock<std::mutex> lock(_cacheMutex);

    auto bytesToWrite = length;
    do
    {
        while (!_closed && (_cache.size() - _cachedBytes) == 0)
        {
            _cacheCondition.wait_for(lock, std::chrono::milliseconds(1000));
        }

        if (_closed)
        {
            throw naranja::exceptions::StreamClosed();
        }
        
        auto bytesToCopy = std::min<std::size_t>(bytesToWrite, std::min<std::size_t>(_cache.size() - _writePosition, _cache.size() - _cachedBytes));
        std::memcpy(&_cache[_writePosition], buffer, bytesToCopy);
        _writePosition = (_writePosition + bytesToCopy) % _cache.size();
        _cachedBytes += bytesToCopy;
        bytesToWrite -= bytesToCopy;
        buffer += bytesToCopy;

        _cacheCondition.notify_one();
    } while (bytesToWrite > 0);
}

void naranja::streams::RigidMemoryStream::Close()
{
    std::unique_lock<std::mutex> lock(_cacheMutex);
    _closed = true;
    _cacheCondition.notify_all();            
}