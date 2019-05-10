#pragma once

#include <cstdint>
#include <mutex>
#include <naranja/core/Exceptions.hpp>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/rpc/IServerSideService.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <naranja/rpc/ServerSideConnection.hpp>
#include <naranja/utils/Disposer.hpp>
#include <naranja/utils/LockableResource.hpp>
#include <string>



namespace naranja
{
    namespace generated
    {
#pragma pack(push, 1)
        class SampleException : public naranja::core::CustomRpcException
        {
        public:
            SampleException() : naranja::core::CustomRpcException() { }
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
        
#pragma pack(pop)

        class ISampleService
        {
        public:
            virtual ~ISampleService() = default;
            
            virtual void FunctionThrowingSampleException() = 0;
            virtual SampleStruct FunctionReturningData(const SampleEnum& arg1) = 0;
            //
            //virtual void SetOnSampleEventCallback(const std::function<void(const std::string& value)>& callback) = 0;
            //
        };

        class SampleServiceProtocol
        {
        public:
            
            static void Write_FunctionThrowingSampleException_Request(protocol::IObjectWriter& objectWriter);
            static void Read_FunctionThrowingSampleException_Request(protocol::IObjectReader& objectReader);
            static void Write_FunctionThrowingSampleException_Response(protocol::IObjectWriter& objectWriter);
            static void Read_FunctionThrowingSampleException_Response(protocol::IObjectReader& objectReader);
            static void Write_FunctionReturningData_Request(protocol::IObjectWriter& objectWriter);
            static void Read_FunctionReturningData_Request(protocol::IObjectReader& objectReader);
            static void Write_FunctionReturningData_Response(protocol::IObjectWriter& objectWriter);
            static void Read_FunctionReturningData_Response(protocol::IObjectReader& objectReader);

            
            static void Write_SampleException(protocol::IObjectWriter& objectWriter);
            static void Read_SampleException(protocol::IObjectReader& objectReader);

            // TODO: events/callbacks
        };
        

    }
}