#pragma once

#include <memory>

namespace naranja
{
    namespace rpc
    {
        class ObjectBroker;

        class IServerSideService
        {
        public:
            virtual ~IServerSideService() = default;

            virtual void RegisterFunctionHandlers(const std::shared_ptr<ObjectBroker>& broker) = 0;
        };
    }
}
