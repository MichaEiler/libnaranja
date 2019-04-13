#pragma once

#include <cstdint>
#include "IInputStream.hpp"

namespace naranja
{
    namespace streams
    {
        class IBufferedInputStream : public IInputStream
        {
        public:
            virtual ~IBufferedInputStream() = default;

            virtual void Peek(char *buffer, const std::size_t length) = 0;
            virtual void Read(char *buffer, const std::size_t length) = 0;

            virtual std::size_t TryPeek(char *buffer, const std::size_t length) override { Peek(buffer, length); return length; }
            virtual std::size_t TryRead(char *buffer, const std::size_t length) override { Read(buffer, length); return length; }
        };
    }
}
