#include "naranja/streams/BufferedInputStream.hpp"

#include <algorithm>
#include <cstring>

naranja::streams::BufferedInputStream::BufferedInputStream(IInputStream& inputStream, const std::size_t cacheSize)
    : _inputStream(inputStream)
    , _cache(cacheSize) {

}


void naranja::streams::BufferedInputStream::ReadAndCache()
{
    const auto endWritePosition = std::min<std::size_t>((_cache.size() - _bytesCached) + _writePosition, _cache.size());
    const auto length = endWritePosition - _writePosition;

    std::size_t bytesRead = 0;
    while (bytesRead == 0)
    {
        bytesRead = _inputStream.TryRead(&_cache[_writePosition], length);
    }

    _writePosition = (_writePosition + bytesRead) % _cache.size();
    _bytesCached += bytesRead;
}

void naranja::streams::BufferedInputStream::Peek(char *buffer, const std::size_t length)
{
    if (length > _cache.size())
    {
        throw std::invalid_argument("Peek request larger than internal buffer.");
    }

    while (_bytesCached < length)
    {
        ReadAndCache();
    }

    const auto initialDataToCopy = std::min<std::size_t>(length, _cache.size() - _readPosition);
    std::memcpy(buffer, &_cache[_readPosition], initialDataToCopy);

    if (initialDataToCopy < length)
    {
        const auto remainingDataToCopy = length - initialDataToCopy;
        std::memcpy(&buffer[initialDataToCopy], _cache.data(), remainingDataToCopy);
    }
}

void naranja::streams::BufferedInputStream::Read(char *buffer, const std::size_t length)
{
    std::size_t bytesToRead = length;

    while (bytesToRead > 0)
    {
        if (_bytesCached == 0)
        {
            ReadAndCache();
        }

        const auto bytesToCopy = std::min(_cache.size() - _readPosition, std::min(length, _bytesCached));
        std::memcpy(buffer + (length - bytesToRead), &_cache[_readPosition], bytesToCopy);
        _readPosition = (_readPosition + bytesToCopy) % _cache.size();
        bytesToRead -= bytesToCopy;
        _bytesCached -= bytesToCopy;
    }
}
