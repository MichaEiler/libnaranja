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
            explicit ObjectBrokerFactory(const std::shared_ptr<IProtocol>& protocol)
                : _protocol(protocol)
            {
            }

            std::shared_ptr<rpc::IBroker> Create() override
            {
                return ObjectBroker::Create(_protocol);
            }
        
        private:
            std::shared_ptr<IProtocol> _protocol;
        };
    }
}