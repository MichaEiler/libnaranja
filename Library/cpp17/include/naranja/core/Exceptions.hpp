#pragma once

#include <stdexcept>

namespace naranja
{
    namespace exceptions
    {
        class StreamClosed : std::exception
        {
        };
    }
}