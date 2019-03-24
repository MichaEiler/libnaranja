#include "Rpc2/Streams/BufferedOutputStream.hpp"

#include <cstring>

Rpc2::Streams::BufferedOutputStream::BufferedOutputStream(const std::shared_ptr<IOutputStream>& outputStream, const std::size_t cacheSize)
    : _outputStream(outputStream)
{
    _cachedData = 0;
    _cache.resize(cacheSize);
}

Rpc2::Streams::BufferedOutputStream::~BufferedOutputStream()
{
    try
    {
        Flush();
    } catch (...)
    { }
}
            
void Rpc2::Streams::BufferedOutputStream::Flush()
{
    if (_cachedData != 0)
    {
        _outputStream->Write(&_cache[0], _cachedData);
        _cachedData = 0;
    }
}

void Rpc2::Streams::BufferedOutputStream::Write(const char *buffer, const std::size_t length)
{
    if (_cache.size() <= length + _cachedData)
    {
        if (_cachedData > 0)
        {
            _outputStream->Write(_cache.data(), _cachedData);
        }

        if (length > 0)
        {
            _outputStream->Write(buffer, length);
        }

        _cachedData = 0;
    }
    else
    {
        std::memcpy(&_cache[_cachedData], buffer, length);
        _cachedData += length;
    }
}
