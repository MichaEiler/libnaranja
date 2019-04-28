#include "SampleService.hpp"

#include <future>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/utils/Disposer.hpp>

// -------------------------------------------------------------------------------------- DeSerialization Routines

void naranja::generated::SampleServiceProtocol::Write_FunctionThrowingSampleException_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

void naranja::generated::SampleServiceProtocol::Read_FunctionThrowingSampleException_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

void naranja::generated::SampleServiceProtocol::Write_FunctionThrowingSampleException_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

void naranja::generated::SampleServiceProtocol::Read_FunctionThrowingSampleException_Response(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

void naranja::generated::SampleServiceProtocol::Write_FunctionReturningData_Request(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::SampleEnum& arg1)
{
    objectWriter.WriteValue("arg1", static_cast<std::uint32_t>(arg1));
}

void naranja::generated::SampleServiceProtocol::Read_FunctionReturningData_Request(naranja::protocol::IObjectReader& objectReader, naranja::generated::SampleEnum& result)
{
    std::uint32_t arg1Encoded;
    objectReader.ReadValue("arg1", arg1Encoded);
    result = static_cast<naranja::generated::SampleEnum>(arg1Encoded);
}

void naranja::generated::SampleServiceProtocol::Write_FunctionReturningData_Response(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::SampleStruct& arg1)
{
    objectWriter.WriteValue("arg1.Member1", arg1.Member1);
    objectWriter.WriteValue("arg1.Member2", arg1.Member2);
}

void naranja::generated::SampleServiceProtocol::Read_FunctionReturningData_Response(naranja::protocol::IObjectReader& objectReader, naranja::generated::SampleStruct& result)
{
    objectReader.ReadValue("arg1.Member1", result.Member1);
    objectReader.ReadValue("arg1.Member2", result.Member2);
}

void naranja::generated::SampleServiceProtocol::Write_SampleException(protocol::IObjectWriter& objectWriter, const SampleException& ex)
{
    objectWriter.WriteValue("Description", ex.Description);
}

void naranja::generated::SampleServiceProtocol::Read_SampleException(protocol::IObjectReader& objectReader, SampleException& ex)
{
    objectReader.ReadValue("Description", ex.Description);
}

// -------------------------------------------------------------------------------------- Client Side Code

naranja::generated::ClientSideSampleService::ClientSideSampleService(const std::shared_ptr<naranja::protocol::ObjectBroker>& broker,
    const std::shared_ptr<naranja::rpc::ClientSideConnection>& connection, const std::shared_ptr<naranja::protocol::IProtocol>& protocol)
    : _broker(broker)
    , _connection(connection)
    , _protocol(protocol)
{
    // TODO: register event callbacks on object broker
}

void naranja::generated::ClientSideSampleService::FunctionThrowingSampleException()
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _broker->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "Sample.SampleException")
            {
                generated::SampleException ex;
                generated::SampleServiceProtocol::Read_SampleException(*objectReader, ex);
                throw ex;
            }
            generated::SampleServiceProtocol::Read_FunctionThrowingSampleException_Response(*objectReader);
            promise.set_value();
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto objectWriter = _protocol->WriteObject(*_connection, naranja::protocol::ObjectType::FunctionCall, "Sample.FunctionThrowingSampleException", token);
    generated::SampleServiceProtocol::Write_FunctionThrowingSampleException_Request(*objectWriter);

    future.get();
}

void naranja::generated::ClientSideSampleService::FunctionReturningData(naranja::generated::SampleStruct& result, const naranja::generated::SampleEnum& arg1)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _broker->RegisterFunctionResponseHandler(token, [this, &promise, &result](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            generated::SampleServiceProtocol::Read_FunctionReturningData_Response(*objectReader, result);
            promise.set_value();
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto objectWriter = _protocol->WriteObject(*_connection, naranja::protocol::ObjectType::FunctionCall, "Sample.FunctionReturningData", token);
    generated::SampleServiceProtocol::Write_FunctionReturningData_Request(*objectWriter, arg1);

    future.get();
}


// -------------------------------------------------------------------------------------- Server Side Code



