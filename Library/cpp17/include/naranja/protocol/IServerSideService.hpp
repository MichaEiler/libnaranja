#pragma once

#include <memory>

namespace naranja
{
    namespace protocol
    {
        class ObjectBroker;

        class IServerSideService
        {
        public:
            virtual ~IServerSideService() = default;

            virtual void AddNewConnection(const std::shared_ptr<protocol::ObjectBroker>& broker) = 0;
        };
    }
}
