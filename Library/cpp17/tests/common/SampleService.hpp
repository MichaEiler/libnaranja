#pragma once

#include <cstdint>
#include <naranja/core/Exceptions.hpp>
#include <naranja/protocol/ObjectBroker.hpp>
#include <naranja/protocol/IProtocol.hpp>
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

            //virtual naranja::utils::Disposer OnSampleEvent(const std::function<void(const std::string&)>& eventHandler) = 0;
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

            //static void Write_SampleEvent(protocol::IObjectWriter& objectWriter, const std::string& value);
            //static void Read_SampleEvent(protocol::IObjectReader& objectReader, std::string& value);
            static void Write_SampleException(protocol::IObjectWriter& objectWriter, const SampleException& ex);
            static void Read_SampleException(protocol::IObjectReader& objectReader, SampleException& ex);
        };


        class ServerSideSampleService
        {
        public:
            explicit ServerSideSampleService(const std::shared_ptr<ISampleService>& service);


            
        private:
            std::shared_ptr<ISampleService> _service;
        };

        class ClientSideSampleService : public ISampleService
        {
        public:
            explicit ClientSideSampleService(const std::shared_ptr<protocol::ObjectBroker>& broker,
                const std::shared_ptr<rpc::ClientSideConnection>& connection, const std::shared_ptr<protocol::IProtocol>& protocol);

            void FunctionThrowingSampleException() override;
            void FunctionReturningData(SampleStruct& result, const SampleEnum& arg1) override;

            //naranja::utils::Disposer OnSampleEvent(const std::function<void(const std::string&)>& eventHandler) override;

        private:
            std::shared_ptr<protocol::ObjectBroker> _broker;
            std::shared_ptr<rpc::ClientSideConnection> _connection;
            std::shared_ptr<protocol::IProtocol> _protocol;
        };
    }
}