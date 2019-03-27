#include "Rpc2/Protocol/One/Protocol.hpp"

#include <Rpc2/Protocol/One/ObjectReader.hpp>
#include <Rpc2/Protocol/One/ObjectWriter.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

Rpc2::Protocol::ObjectToken Rpc2::Protocol::One::Protocol::CreateToken()
{
    std::lock_guard<std::mutex> lock(_tokenMutex);
    auto tokenNumber = _tokenCounter++;

    std::stringstream memoryStream;
    memoryStream << std::hex << std::setw(8) << std::setfill('0') << tokenNumber;

    return ObjectToken(memoryStream.str());
}

Rpc2::Protocol::ObjectToken Rpc2::Protocol::One::Protocol::PeekNextToken(const std::shared_ptr<Rpc2::Streams::BufferedInputStream>& stream)
{
    if (PeekNextObjectType(stream) == Rpc2::Protocol::ObjectType::Event)
    {
        throw std::runtime_error("Invalid operation. Next object is an event.");
    }

    constexpr std::size_t ObjectTypeSize = sizeof(std::uint32_t);
    constexpr std::size_t TokenLengthOffset = ObjectTypeSize;
    constexpr std::size_t TokenLengthTypeSize = sizeof(std::uint64_t);

    std::vector<char> buffer(ObjectTypeSize + TokenLengthTypeSize);
    stream->Peek(reinterpret_cast<char*>(&buffer[0]), buffer.size());

    const std::uint64_t tokenLength = *reinterpret_cast<std::uint64_t*>(&buffer[TokenLengthOffset]);
    buffer.resize(buffer.size() + tokenLength);
    stream->Peek(&buffer[0], buffer.size());

    return Rpc2::Protocol::ObjectToken(buffer.data() + ObjectTypeSize + TokenLengthTypeSize, static_cast<std::size_t>(tokenLength));
}

Rpc2::Protocol::ObjectType Rpc2::Protocol::One::Protocol::PeekNextObjectType(const std::shared_ptr<Rpc2::Streams::BufferedInputStream>& stream)
{
    std::uint32_t encodedType = 0;
    stream->Peek(reinterpret_cast<char*>(&encodedType), sizeof(std::uint32_t));
    return static_cast<Rpc2::Protocol::ObjectType>(encodedType);
}

std::shared_ptr<Rpc2::Protocol::IObjectWriter> Rpc2::Protocol::One::Protocol::WriteObject(const std::shared_ptr<Rpc2::Streams::BufferedOutputStream>& stream, const Rpc2::Protocol::ObjectType& type, const Rpc2::Protocol::ObjectIdentifier& identifier, const Rpc2::Protocol::ObjectToken& token)
{
    auto objectWriter = std::make_shared<Rpc2::Protocol::One::ObjectWriter>(stream);

    objectWriter->WriteValue("", static_cast<std::uint32_t>(type));

    if (type != Rpc2::Protocol::ObjectType::Event)
    {
        objectWriter->WriteValue("", token);
    }
    objectWriter->WriteValue("", identifier);

    return objectWriter;
}

std::shared_ptr<Rpc2::Protocol::IObjectReader> Rpc2::Protocol::One::Protocol::ReadObject(const std::shared_ptr<Rpc2::Streams::BufferedInputStream>& stream)
{
    auto object = std::make_shared<Rpc2::Protocol::One::ObjectReader>(stream);

    std::uint32_t encodedType = 0;
    object->ReadValue("", encodedType);
    object->Type(static_cast<Rpc2::Protocol::ObjectType>(encodedType));

    Rpc2::Protocol::ObjectToken token("");
    Rpc2::Protocol::ObjectIdentifier identifier("");

    if (object->Type() != Rpc2::Protocol::ObjectType::Event)
    {
        object->ReadValue("", token);
    }
    
    object->ReadValue("", identifier);

    object->Token(token);
    object->Identifier(identifier);

    return object;
}

