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
            explicit RigidMemoryStream(const std::size_t cacheSize = 64 * 1024);
            ~RigidMemoryStream() override;

            std::size_t AvailableBytes() const;
            std::size_t TryPeek(char* buffer, const std::size_t length) override;
            std::size_t TryRead(char* buffer, const std::size_t length) override;
            void Write(const char* buffer, const std::size_t length);
            void Close();

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
