#pragma once

#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <naranja/core/Exceptions.hpp>
#include <naranja/streams/IInputStream.hpp>
#include <naranja/streams/IOutputStream.hpp>
#include <vector>

namespace naranja
{
    namespace streams
    {
        class RigidMemoryStream final : public IOutputStream, public IInputStream
        {
        public:
            explicit RigidMemoryStream(const std::size_t cacheSize = 64 * 1024)
                : _cache(cacheSize, 0)
            {

            }

            ~RigidMemoryStream() override
            {

            }

            std::size_t AvailableBytes() const { return _cachedBytes; }

            std::size_t TryPeek(char* buffer, const std::size_t length) override
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

            std::size_t TryRead(char* buffer, const std::size_t length) override
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

            void Write(const char* buffer, const std::size_t length)
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

            void Close()
            {
                std::unique_lock<std::mutex> lock(_cacheMutex);
                _closed = true;
                _cacheCondition.notify_all();            
            }

        private:
            bool _closed = false;
            
            std::size_t _cachedBytes = 0;
            std::size_t _readPosition = 0;
            std::size_t _writePosition = 0;

            mutable std::mutex _cacheMutex;
            mutable std::condition_variable _cacheCondition;
            std::vector<char> _cache;
        };
    }
}
