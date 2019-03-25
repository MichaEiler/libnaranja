#pragma once

#include <chrono>
#include <Core/Exceptions.hpp>
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <Rpc2/Streams/IInputStream.hpp>
#include <Rpc2/Streams/IOutputStream.hpp>
#include <vector>

namespace Rpc2
{
    namespace Streams
    {
        class MemoryStream final : public IOutputStream, public IInputStream
        {
        public:
            explicit MemoryStream(const std::size_t cacheSize = 64 * 1024)
                : _cache(cacheSize, 0)
            {

            }

            ~MemoryStream() override
            {

            }

            std::size_t Read(char* buffer, const std::size_t length)
            {
                std::unique_lock<std::mutex> lock(_cacheMutex);

                while (!_closed && _cachedBytes == 0)
                {
                    _cacheCondition.wait_for(lock, std::chrono::milliseconds(1000));
                }

                if (_cachedBytes == 0 && _closed)
                {
                    throw Rpc2::Exceptions::StreamClosed();
                }

                const auto bytesToCopy = std::min<std::size_t>(std::min<std::size_t>(length, (_cache.size() - _readPosition)), _cachedBytes);
                std::memcpy(buffer, _cache.data(), bytesToCopy);
                _cachedBytes -= bytesToCopy;
                _readPosition = (_readPosition + bytesToCopy) % _cache.size();

                if (length > bytesToCopy && _cachedBytes > 0)
                {
                    const auto remainingBytesToCopy = std::min<std::size_t>(length - bytesToCopy, _cachedBytes);
                    std::memcpy(buffer + bytesToCopy, _cache.data(), remainingBytesToCopy);
                    _cachedBytes -= remainingBytesToCopy;
                    _readPosition = (_readPosition + bytesToCopy) % _cache.size();
                }

                _cacheCondition.notify_one();
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
                        throw Rpc2::Exceptions::StreamClosed();
                    }
                    
                    auto bytesToCopy = std::min<std::size_t>(bytesToWrite, std::min<std::size_t>(_cache.size() - _writePosition, _cache.size() - _cachedBytes));
                    std::memcpy(&_cache[_writePosition], buffer, bytesToCopy);
                    _writePosition = (_writePosition + bytesToCopy) & _cache.size();
                    _cachedBytes += bytesToCopy;
                    bytesToWrite -= bytesToCopy;

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

            std::mutex _cacheMutex;
            std::condition_variable _cacheCondition;
            std::vector<char> _cache;
        };
    }
}