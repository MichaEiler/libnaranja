#pragma once

#include <cstdint>
#include <mutex>
#include <naranja/core/Exceptions.hpp>
#include <naranja/protocol/ObjectBroker.hpp>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/protocol/IServerSideService.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <naranja/utils/Disposer.hpp>
#include <string>

namespace naranja
{
    namespace protocol
    {
        class IObjectReader;
        class IObjectWriter;
    }

    namespace generated
    {
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

        class SampleException : public naranja::core::CustomRpcException
        {
        public:
            SampleException() : naranja::core::CustomRpcException() { }

            std::string Description;
        };

        class ISampleService
        {
        public:
            virtual ~ISampleService() = default;

            virtual void FunctionThrowingSampleException() = 0;
            virtual void FunctionReturningData(SampleStruct& result, const SampleEnum& arg1) = 0;

            virtual naranja::utils::Disposer OnSampleEvent(const std::function<void(const std::string& value)>& eventHandler) = 0;
        };

        class SampleServiceProtocol final
        {
        public:
            static void Write_FunctionThrowingSampleException_Request(protocol::IObjectWriter& objectWriter);
            static void Read_FunctionThrowingSampleException_Request(protocol::IObjectReader& objectReader);
            static void Write_FunctionThrowingSampleException_Response(protocol::IObjectWriter& objectWriter);
            static void Read_FunctionThrowingSampleException_Response(protocol::IObjectReader& objectReader);

            static void Write_FunctionReturningData_Request(protocol::IObjectWriter& objectWriter, const SampleEnum& arg1);
            static void Read_FunctionReturningData_Request(protocol::IObjectReader& objectReader, SampleEnum& result);
            static void Write_FunctionReturningData_Response(protocol::IObjectWriter& objectWriter, const SampleStruct& arg1);
            static void Read_FunctionReturningData_Response(protocol::IObjectReader& objectReader, SampleStruct& result);

            static void Write_SampleEvent(protocol::IObjectWriter& objectWriter, const std::string& value);
            static void Read_SampleEvent(protocol::IObjectReader& objectReader, std::string& value);
            static void Write_SampleException(protocol::IObjectWriter& objectWriter, const SampleException& ex);
            static void Read_SampleException(protocol::IObjectReader& objectReader, SampleException& ex);
        };


        class ServerSideSampleService : public naranja::protocol::IServerSideService, public std::enable_shared_from_this<ServerSideSampleService>
        {
        public:
            static std::shared_ptr<ServerSideSampleService> Create(const std::shared_ptr<ISampleService>& service, const std::shared_ptr<protocol::IProtocol>& protocol)
            {
                return std::shared_ptr<ServerSideSampleService>(new ServerSideSampleService(service, protocol));
            }

            void AddNewConnection(const std::shared_ptr<protocol::ObjectBroker>& broker) override
            {
                broker->RegisterFunctionCallHandler("Sample.FunctionThrowingSampleException", 
                    [weakService = std::weak_ptr<ServerSideSampleService>(shared_from_this())](auto& object){
                        auto strongService = weakService.lock();
                        if (!strongService)
                        {
                            return;
                        }

                        strongService->FunctionThrowingSampleException(*object, outputStream);
                    }).Clear();
            }
            
        private:
            explicit ServerSideSampleService(const std::shared_ptr<ISampleService>& service, const std::shared_ptr<protocol::IProtocol>& protocol);

            void FunctionThrowingSampleException(protocol::IObjectReader& object, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream);
            void FunctionReturningData(protocol::IObjectReader& object, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream);

            std::shared_ptr<protocol::IProtocol> _protocol;
            std::shared_ptr<ISampleService> _service;
        };

        class ClientSideSampleService : public ISampleService, public std::enable_shared_from_this<ClientSideSampleService>
        {
        public:
            static std::shared_ptr<ClientSideSampleService> Create(const std::shared_ptr<protocol::ObjectBroker>& broker,
                const std::shared_ptr<rpc::ClientSideConnection>& connection, const std::shared_ptr<protocol::IProtocol>& protocol)
            {
                return std::shared_ptr<ClientSideSampleService>(new ClientSideSampleService(broker, connection, protocol));
            }

            void FunctionThrowingSampleException() override;
            void FunctionReturningData(SampleStruct& result, const SampleEnum& arg1) override;

            naranja::utils::Disposer OnSampleEvent(const std::function<void(const std::string& value)>& eventHandler) override;

        private:
            explicit ClientSideSampleService(const std::shared_ptr<protocol::ObjectBroker>& broker,
                const std::shared_ptr<rpc::ClientSideConnection>& connection, const std::shared_ptr<protocol::IProtocol>& protocol);

            std::shared_ptr<protocol::ObjectBroker> _broker;
            std::shared_ptr<rpc::ClientSideConnection> _connection;
            std::shared_ptr<protocol::IProtocol> _protocol;

            std::mutex _eventMutex;

            naranja::utils::Disposer _sampleEventRegistrationDisposer;
            std::unordered_map<protocol::ObjectToken, std::function<void(const std::string&)>> _sampleEventListeners;
        };
    }
}