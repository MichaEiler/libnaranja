#pragma once

#include <stdexcept>

namespace naranja
{
    namespace exceptions
    {
        class ConnectionClosed : std::exception
        {
        };

        class StreamClosed : std::exception
        {
        };
    }
}