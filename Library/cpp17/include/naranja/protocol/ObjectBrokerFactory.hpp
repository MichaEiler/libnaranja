#pragma once

#include <naranja/protocol/ObjectBroker.hpp>
#include <naranja/rpc/IBrokerFactory.hpp>

namespace naranja
{
    namespace protocol
    {
        class ObjectBrokerFactory : public rpc::IBrokerFactory
        {
        public:
            std::shared_ptr<rpc::IBroker> Create() override
            {
                return std::make_shared<ObjectBroker>();
            }
        };
    }
}