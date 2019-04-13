#pragma once

#include <cstdint>
#include "IOutputStream.hpp"

namespace naranja
{
    namespace streams
    {
        class IBufferedOutputStream : public IOutputStream
        {
        public:
            virtual ~IBufferedOutputStream() = default;

            virtual void Flush() = 0;
        };
    }
}
