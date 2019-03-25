#pragma once

#include <stdexcept>

namespace Rpc2
{
    namespace Exceptions
    {
        class StreamClosed : std::exception
        {
        };
    }
}