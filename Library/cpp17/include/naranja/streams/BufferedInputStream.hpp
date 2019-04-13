#pragma once

#include <cstdint>
#include <memory>
#include <naranja/streams/IBufferedInputStream.hpp>
#include <vector>

namespace naranja
{
    namespace streams
    {
        class BufferedInputStream : public IBufferedInputStream
        {
        public:
            static std::shared_ptr<BufferedInputStream> Create(const std::shared_ptr<IInputStream>& inputStream, const std::size_t cacheSize = 512 * 1024)
            {
                return std::shared_ptr<BufferedInputStream>(new BufferedInputStream(*inputStream, cacheSize), [inputStream](auto* ptr) { delete ptr; });
            }

            explicit BufferedInputStream(IInputStream& inputStream, const std::size_t cacheSize = 512 * 1024);
            virtual ~BufferedInputStream() noexcept override = default;

            std::size_t AvailableBytes() const { return _bytesCached; }
            void Peek(char *buffer, const std::size_t length) override;
            void Read(char *buffer, const std::size_t length) override;

        private:
            void ReadAndCache();

            IInputStream& _inputStream;
            std::vector<char> _cache;
            std::size_t _bytesCached = 0;
            std::size_t _readPosition = 0;
            std::size_t _writePosition = 0;
        };
    }
}
