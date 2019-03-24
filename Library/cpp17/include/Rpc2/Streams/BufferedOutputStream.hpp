#pragma once

#include <cstdint>
#include <memory>
#include <Rpc2/Streams/IOutputStream.hpp>
#include <vector>

namespace Rpc2
{
    namespace Streams
    {
        class BufferedOutputStream : public IOutputStream
        {
        public:
            static std::shared_ptr<BufferedOutputStream> Create(const std::shared_ptr<IOutputStream>& outputStream, const std::size_t cacheSize = 512 * 1024)
            {
                return std::shared_ptr<BufferedOutputStream>(new BufferedOutputStream(outputStream, cacheSize));
            }

            explicit BufferedOutputStream(const std::shared_ptr<IOutputStream>& outputStream, const std::size_t cacheSize = 512 * 1024);
            virtual ~BufferedOutputStream() noexcept override;
            
            void Flush();
            void Write(const char *buffer, const std::size_t length) override;

        private:
            std::shared_ptr<IOutputStream> _outputStream;
            std::vector<char> _cache;
            std::size_t _cachedData;
        };
    }
}
