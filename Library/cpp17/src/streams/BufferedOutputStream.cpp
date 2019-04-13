#include "naranja/streams/BufferedOutputStream.hpp"

#include <cstring>

naranja::streams::BufferedOutputStream::BufferedOutputStream(IOutputStream& outputStream, const std::size_t cacheSize)
    : _outputStream(outputStream)
{
    _cachedData = 0;
    _cache.resize(cacheSize);
}

naranja::streams::BufferedOutputStream::~BufferedOutputStream()
{
    try
    {
        Flush();
    } catch (...)
    { }
}
            
void naranja::streams::BufferedOutputStream::Flush()
{
    if (_cachedData != 0)
    {
        _outputStream.Write(&_cache[0], _cachedData);
        _cachedData = 0;
    }
}

void naranja::streams::BufferedOutputStream::Write(const char *buffer, const std::size_t length)
{
    if (_cache.size() <= length + _cachedData)
    {
        if (_cachedData > 0)
        {
            _outputStream.Write(_cache.data(), _cachedData);
        }

        if (length > 0)
        {
            _outputStream.Write(buffer, length);
        }

        _cachedData = 0;
    }
    else
    {
        std::memcpy(&_cache[_cachedData], buffer, length);
        _cachedData += length;
    }
}
