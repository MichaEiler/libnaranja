#include "SampleService.hpp"

#include <future>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/utils/Disposer.hpp>

// -------------------------------------------------------------------------------------- DeSerialization Routines

{% for function in service.functions %}
void naranja::generated::SampleServiceProtocol::Write_{{ function.name }}_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

void naranja::generated::SampleServiceProtocol::Read_{{ function.name }}_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

void naranja::generated::SampleServiceProtocol::Write_{{ function.name }}_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

void naranja::generated::SampleServiceProtocol::Read_{{ function.name }}_Response(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}
{%- endfor %}


// -------------------------------------------------------------------------------------- Client Side Code



// -------------------------------------------------------------------------------------- Server Side Code


