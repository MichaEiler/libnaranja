#pragma once

// This code is generated. It is not recommended to manually manipulate it!
// Generator: NaranjaTool, 0.0.0.3
// 2019-05-28 20:16:00.209717

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
                
                virtual void TransmitStruct(const SampleStruct& arg) = 0;
                virtual void TransmitEnum(const SampleEnum& arg) = 0;
                virtual void TransmitInteger(const std::int64_t& arg) = 0;
                virtual void TransmitString(const std::string& arg) = 0;
                virtual void TransmitBinary(const std::vector<char>& arg) = 0;
                virtual void TransmitListOfIntegers(const std::list<std::int64_t>& arg) = 0;
                virtual void TransmitListOfStructs(const std::list<SampleStruct>& arg) = 0;
                virtual SampleStruct ReceiveStruct() = 0;
                virtual SampleEnum ReceiveEnum() = 0;
                virtual std::int64_t ReceiveInteger() = 0;
                virtual std::string ReceiveString() = 0;
                virtual std::vector<char> ReceiveBinary() = 0;
                virtual std::list<std::int64_t> ReceiveListOfIntegers() = 0;
                virtual std::list<SampleStruct> ReceiveListOfStructs() = 0;
                virtual void CallFailingFunction() = 0;
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

                
                void TransmitStruct(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void TransmitEnum(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void TransmitInteger(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void TransmitString(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void TransmitBinary(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void TransmitListOfIntegers(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void TransmitListOfStructs(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void ReceiveStruct(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void ReceiveEnum(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void ReceiveInteger(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void ReceiveString(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void ReceiveBinary(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void ReceiveListOfIntegers(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void ReceiveListOfStructs(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);
                void CallFailingFunction(protocol::IObjectReader& object, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection);

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
                
                
                void TransmitStruct(const SampleStruct& arg) override;
                void TransmitEnum(const SampleEnum& arg) override;
                void TransmitInteger(const std::int64_t& arg) override;
                void TransmitString(const std::string& arg) override;
                void TransmitBinary(const std::vector<char>& arg) override;
                void TransmitListOfIntegers(const std::list<std::int64_t>& arg) override;
                void TransmitListOfStructs(const std::list<SampleStruct>& arg) override;
                SampleStruct ReceiveStruct() override;
                SampleEnum ReceiveEnum() override;
                std::int64_t ReceiveInteger() override;
                std::string ReceiveString() override;
                std::vector<char> ReceiveBinary() override;
                std::list<std::int64_t> ReceiveListOfIntegers() override;
                std::list<SampleStruct> ReceiveListOfStructs() override;
                void CallFailingFunction() override;

            private:
                explicit ClientSideSampleService(const std::shared_ptr<rpc::ClientSideConnection>& connection,
                    const std::shared_ptr<protocol::IProtocol>& protocol);

                std::shared_ptr<rpc::ClientSideConnection> _connection;
                std::shared_ptr<protocol::IProtocol> _protocol;
            };
            
        }
    }
}