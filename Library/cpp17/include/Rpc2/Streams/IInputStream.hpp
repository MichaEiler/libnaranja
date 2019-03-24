#pragma once

#include <cstdint>

namespace Rpc2
{
    namespace Streams
    {
        class IInputStream
        {
        public:
            virtual ~IInputStream() = default;
            virtual std::size_t Read(char *buffer, const std::size_t length) = 0;
        };
    }
}
