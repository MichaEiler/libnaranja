#pragma once

#include <memory>

namespace naranja
{
    namespace rpc
    {
        class IBroker;

        class IServerSideService
        {
        public:
            virtual ~IServerSideService() = default;

            virtual void AddNewConnection(const std::shared_ptr<rpc::IBroker>& broker) = 0;
        };
    }
}
