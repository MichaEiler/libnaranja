#pragma once

#include <cstdint>

namespace naranja
{
    namespace streams
    {
        class IOutputStream
        {
        public:
            virtual ~IOutputStream() = default;

            virtual void Write(const char *buffer, const std::size_t length) = 0;
        };
    }
}
