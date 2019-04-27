#pragma once

#include <memory>

namespace naranja
{
    namespace rpc
    {
        class IBroker;

        class IBrokerFactory
        {
        public:
            virtual ~IBrokerFactory() = default;

            virtual std::shared_ptr<IBroker> Create() = 0;
        };
    }
}