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

naranja::protocol::ObjectToken naranja::protocol::one::Protocol::PeekNextToken(naranja::streams::IBufferedInputStream& stream)
{
    if (PeekNextObjectType(stream) == naranja::protocol::ObjectType::Event)
    {
        throw std::runtime_error("Invalid operation. Next object is an event.");
    }

    constexpr std::size_t ObjectTypeSize = sizeof(std::uint32_t);
    constexpr std::size_t TokenLengthOffset = ObjectTypeSize;
    constexpr std::size_t TokenLengthTypeSize = sizeof(std::uint64_t);

    std::vector<char> buffer(ObjectTypeSize + TokenLengthTypeSize);
    stream.Peek(reinterpret_cast<char*>(&buffer[0]), buffer.size());

    const std::uint64_t tokenLength = *reinterpret_cast<std::uint64_t*>(&buffer[TokenLengthOffset]);
    buffer.resize(buffer.size() + tokenLength);
    stream.Peek(&buffer[0], buffer.size());

    return naranja::protocol::ObjectToken(buffer.data() + ObjectTypeSize + TokenLengthTypeSize, static_cast<std::size_t>(tokenLength));
}

naranja::protocol::ObjectType naranja::protocol::one::Protocol::PeekNextObjectType(naranja::streams::IBufferedInputStream& stream)
{
    std::uint32_t encodedType = 0;
    stream.Peek(reinterpret_cast<char*>(&encodedType), sizeof(std::uint32_t));
    return static_cast<naranja::protocol::ObjectType>(encodedType);
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

