#pragma once

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <naranja/streams/IInputStream.hpp>
#include <naranja/streams/IOutputStream.hpp>
#include <vector>

namespace naranja
{
    namespace streams
    {
        class MemoryStream final : public IOutputStream, public IInputStream
        {
        public:
            explicit MemoryStream(const std::size_t cacheSize = 64 * 1024);

            std::size_t AvailableBytes() const override;
            std::size_t TryPeek(char* buffer, const std::size_t length) override;
            std::size_t TryRead(char* buffer, const std::size_t length) override;
            void Write(const char* buffer, const std::size_t length) override;
            std::size_t Capacity() const;

        private:
            std::size_t _cachedBytes = 0;
            std::size_t _readPosition = 0;
            std::size_t _writePosition = 0;

            std::vector<char> _cache;
        };
    }
}
