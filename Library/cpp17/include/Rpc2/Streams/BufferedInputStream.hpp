#pragma once

#include <cstdint>
#include <memory>
#include <Rpc2/Streams/IInputStream.hpp>
#include <vector>

namespace Rpc2
{
    namespace Streams
    {
        class BufferedInputStream : public IInputStream
        {
        public:
            static std::shared_ptr<BufferedInputStream> Create(const std::shared_ptr<IInputStream>& inputStream, const std::size_t cacheSize = 512 * 1024)
            {
                return std::shared_ptr<BufferedInputStream>(new BufferedInputStream(inputStream, cacheSize));
            }

            explicit BufferedInputStream(const std::shared_ptr<IInputStream>& inputStream, const std::size_t cacheSize = 512 * 1024);
            virtual ~BufferedInputStream() noexcept override = default;

            void Peek(char *buffer, const std::size_t length);
            std::size_t Read(char *buffer, const std::size_t length) override;

        private:
            void ReadAndCache();

            std::shared_ptr<IInputStream> _inputStream;
            std::vector<char> _cache;
            std::size_t _bytesCached = 0;
            std::size_t _readPosition = 0;
            std::size_t _writePosition = 0;
        };
    }
}
