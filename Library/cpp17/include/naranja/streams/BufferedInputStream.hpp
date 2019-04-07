#pragma once

#include <cstdint>
#include <memory>
#include <naranja/streams/IInputStream.hpp>
#include <vector>

namespace naranja
{
    namespace streams
    {
        class BufferedInputStream : public IInputStream
        {
        public:
            explicit BufferedInputStream(const std::shared_ptr<IInputStream>& inputStream, const std::size_t cacheSize = 512 * 1024);
            virtual ~BufferedInputStream() noexcept override = default;

            void Peek(char *buffer, const std::size_t length);

            /*
             * Read operation blocks until length bytes have been received.
             * @returns: length
             */
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
