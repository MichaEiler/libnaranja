#pragma once

#include <cstdint>
#include <naranja/core/Exceptions.hpp>
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

            static void Write_SampleException(protocol::IObjectWriter& objectWriter, const std::string& description);
            static void ReadAndThrow_SampleException(protocol::IObjectReader& objectReader);
        };


        class ServerSideSampleService
        {
        public:

        };

        class ClientSideSampleService
        {
        public:

        };
    }
}