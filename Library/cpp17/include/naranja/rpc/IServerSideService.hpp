#pragma once

#include <memory>

namespace naranja
{
    namespace rpc
    {
        class ServerSideConnection;

        class IServerSideService
        {
        public:
            virtual ~IServerSideService() = default;

            virtual void RegisterNewConnection(const std::shared_ptr<ServerSideConnection>& connection) = 0;
        };
    }
}
