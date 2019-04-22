#include "naranja/protocol/one/Protocol.hpp"

#include <naranja/protocol/one/ObjectReader.hpp>
#include <naranja/protocol/one/ObjectWriter.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

naranja::protocol::ObjectToken naranja::protocol::one::Protocol::CreateToken()
{
    std::lock_guard<std::mutex> lock(_tokenMutex);
    auto tokenNumber = _tokenCounter++;

    std::stringstream memoryStream;
    memoryStream << std::hex << std::setw(8) << std::setfill('0') << tokenNumber;

    return ObjectToken(memoryStream.str());
}

std::shared_ptr<naranja::protocol::IObjectWriter> naranja::protocol::one::Protocol::WriteObject(naranja::streams::IBufferedOutputStream& stream, const naranja::protocol::ObjectType& type, const naranja::protocol::ObjectIdentifier& identifier, const naranja::protocol::ObjectToken& token) const
{
    auto objectWriter = std::make_shared<naranja::protocol::one::ObjectWriter>(stream);

    objectWriter->WriteValue("", static_cast<std::uint32_t>(type));

    if (type != naranja::protocol::ObjectType::Event)
    {
        objectWriter->WriteValue("", token);
    }
    objectWriter->WriteValue("", identifier);

    return objectWriter;
}

std::shared_ptr<naranja::protocol::IObjectReader> naranja::protocol::one::Protocol::ReadObject(naranja::streams::IBufferedInputStream& stream) const
{
    auto object = std::make_shared<naranja::protocol::one::ObjectReader>(stream);

    std::uint32_t encodedType = 0;
    object->ReadValue("", encodedType);
    object->Type(static_cast<naranja::protocol::ObjectType>(encodedType));

    naranja::protocol::ObjectToken token("");
    naranja::protocol::ObjectIdentifier identifier("");

    if (object->Type() != naranja::protocol::ObjectType::Event)
    {
        object->ReadValue("", token);
    }
    
    object->ReadValue("", identifier);

    object->Token(token);
    object->Identifier(identifier);

    return object;
}

