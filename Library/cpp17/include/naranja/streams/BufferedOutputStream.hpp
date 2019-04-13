#pragma once

#include <cstdint>
#include <memory>
#include <naranja/streams/IBufferedOutputStream.hpp>
#include <vector>

namespace naranja
{
    namespace streams
    {
        class BufferedOutputStream : public IBufferedOutputStream
        {
        public:
            static std::shared_ptr<BufferedOutputStream> Create(const std::shared_ptr<IOutputStream>& outputStream, const std::size_t cacheSize = 512 * 1024)
            {
                return std::shared_ptr<BufferedOutputStream>(new BufferedOutputStream(*outputStream, cacheSize), [](auto *ptr) { delete ptr; });
            }

            explicit BufferedOutputStream(IOutputStream& outputStream, const std::size_t cacheSize = 512 * 1024);
            virtual ~BufferedOutputStream() noexcept override;
            
            void Flush() override;
            void Write(const char *buffer, const std::size_t length) override;

        private:
            IOutputStream& _outputStream;
            std::vector<char> _cache;
            std::size_t _cachedData;
        };
    }
}
