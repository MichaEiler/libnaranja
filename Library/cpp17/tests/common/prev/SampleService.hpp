#pragma once

// This code is generated. It is not recommended to manually manipulate it!
// Generator: NaranjaTool, 0.0.0.3
// 2019-05-17 18:41:03.564995

#include <cstdint>
#include <naranja/core/Exceptions.hpp>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/rpc/IServerSideService.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <naranja/rpc/ServerSideConnection.hpp>
#include <naranja/utils/Disposer.hpp>
#include <string>
#include <vector>



namespace naranja
{
    namespace generated
    {
        namespace Sample
        {
            class SampleException : public naranja::core::CustomRpcException
            {
            public:
                std::string Description;
            };
            
            enum class SampleEnum : std::uint32_t
            {
                Entry0 = 0,
                Entry1 = 1,
            };
            
            struct SampleStruct
            {
                std::int64_t Member1;
                std::string Member2;
            };
            

            class ISampleService
            {
            public:
                virtual ~ISampleService() = default;
                
                virtual void FunctionThrowingSampleException() = 0;
                virtual SampleStruct FunctionReturningData(const SampleEnum&arg1) = 0;
            };

            class ServerSideSampleService : public naranja::rpc::IServerSideService, public std::enable_shared_from_this<ServerSideSampleService>
            {
            public:
                static std::shared_ptr<ServerSideSampleService> Create(const std::shared_ptr<ISampleService>& service, const std::shared_ptr<protocol::IProtocol>& protocol)
                {
                    return std::shared_ptr<ServerSideSampleService>(new ServerSideSampleService(service, protocol));
                }

                void RegisterNewConnection(const std::shared_ptr<rpc::ServerSideConnection>& connection) override;
                
            private:
                explicit ServerSideSampleService(const std::shared_ptr<ISampleService>& service, const std::shared_ptr<protocol::IProtocol>& protocol);

                void ConnectHandler(const std::shared_ptr<rpc::ServerSideConnection>& connection, const std::string& identifier,
                    void (ServerSideSampleService::*const func)(protocol::IObjectReader&, const std::shared_ptr<naranja::rpc::ServerSideConnection>&))
                {
                    connection->RegisterFunctionCallHandler(identifier, [weakService = std::weak_ptr<ServerSideSampleService>(shared_from_this()), func](auto& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection){
                            auto strongService = weakService.lock();
                            if (!strongService)
                            {
                                return;
                            }

                            auto& objectRef = *object;
                            (*strongService.*func)(objectRef, connection);
                        }).Clear();
                }

                
                void FunctionThrowingSampleException(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void FunctionReturningData(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);

                std::shared_ptr<protocol::IProtocol> _protocol;
                std::shared_ptr<ISampleService> _service;
            };

            class ClientSideSampleService : public ISampleService, public std::enable_shared_from_this<ClientSideSampleService>
            {
            public:
                static std::shared_ptr<ClientSideSampleService> Create(const std::shared_ptr<rpc::ClientSideConnection>& connection,
                    const std::shared_ptr<protocol::IProtocol>& protocol)
                {
                    return std::shared_ptr<ClientSideSampleService>(new ClientSideSampleService(connection, protocol));
                }
                
                
                void FunctionThrowingSampleException() override;
                SampleStruct FunctionReturningData(const SampleEnum&arg1) override;

            private:
                explicit ClientSideSampleService(const std::shared_ptr<rpc::ClientSideConnection>& connection,
                    const std::shared_ptr<protocol::IProtocol>& protocol);

                std::shared_ptr<rpc::ClientSideConnection> _connection;
                std::shared_ptr<protocol::IProtocol> _protocol;
            };
            
        }
    }
}