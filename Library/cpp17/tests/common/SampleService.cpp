#include "SampleService.hpp"

#include <naranja/protocol/IProtocol.hpp>

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

void naranja::generated::SampleServiceProtocol::Write_SampleException(naranja::protocol::IObjectWriter& objectWriter, const std::string& description)
{
    objectWriter.WriteValue("Description", description);
}

void naranja::generated::SampleServiceProtocol::ReadAndThrow_SampleException(naranja::protocol::IObjectReader& objectReader)
{
    SampleException exception{};
    
    objectReader.ReadValue("Description", exception.Description);

    throw exception;
}
