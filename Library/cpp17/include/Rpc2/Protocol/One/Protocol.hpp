#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <Rpc2/Protocol/IProtocol.hpp>
#include <Rpc2/Streams/BufferedOutputStream.hpp>
#include <string>

namespace Rpc2
{
    namespace Protocol
    {
        namespace One
        {
            class ObjectReader : public IObjectReader, public std::enable_shared_from_this<ObjectReader>
            {
            public:
                explicit ObjectReader(const std::shared_ptr<::Rpc2::Streams::BufferedInputStream>& stream)
                    : _stream(stream)
                {
                }

                ObjectToken Token() const override { return _token; }
                ObjectType Type() const override { return _type; }
                ObjectIdentifier Identifier() const override { return _identifier; }

                void Token(const ObjectToken& token) { _token = token; }
                void Type(const ObjectType& type) { _type = type; }
                void Identifier(const ObjectIdentifier& identifier) { _identifier = identifier; }

                void ReadValue(const std::string_view&, std::uint64_t& value) override { Read(value); }
                void ReadValue(const std::string_view&, std::uint32_t& value) override { Read(value); }
                void ReadValue(const std::string_view&, std::uint16_t& value) override { Read(value); }
                void ReadValue(const std::string_view&, std::uint8_t& value) override { Read(value); }
                void ReadValue(const std::string_view&, std::int64_t& value) override { Read(value); }
                void ReadValue(const std::string_view&, std::int32_t& value) override { Read(value); }
                void ReadValue(const std::string_view&, std::int16_t& value) override { Read(value); }
                void ReadValue(const std::string_view&, std::int8_t& value) override { Read(value); }

                void ReadValue(const std::string_view&, bool& value) override
                {
                    std::uint8_t encodedValue = 0;
                    Read(encodedValue);
                    value = encodedValue != 0;
                }

                void ReadValue(const std::string_view&, std::string& value) override
                {
                    std::uint64_t length = 0;
                    Read(length);
                    value.resize(length);
                    _stream->Read(&value[0], value.size());
                }

                void ReadValue(const std::string_view&, std::vector<char>& value) override
                {
                    std::uint64_t length = 0;
                    Read(length);
                    value.resize(length);
                    _stream->Read(&value[0], value.size());
                }

                std::shared_ptr<IObjectReader> ReadList(const std::string_view&, std::size_t& itemCount) override
                {
                    std::uint32_t itemCountInt = 0;
                    Read(itemCountInt);
                    itemCount = static_cast<std::size_t>(itemCountInt);
                    return shared_from_this();
                }

                std::shared_ptr<IObjectReader> ReadObject(const std::string_view&) override
                {
                    return shared_from_this();
                }

            private:
                template <typename T>
                void Read(T& value)
                {
                    _stream->Read(reinterpret_cast<char*>(&value), sizeof(T));
                }

                ObjectIdentifier _identifier;
                ObjectToken _token;
                ObjectType _type;

                std::shared_ptr<Rpc2::Streams::BufferedInputStream> _stream;
            };

            class ObjectWriter : public IObjectWriter, public std::enable_shared_from_this<ObjectWriter>
            {
            public:
                explicit ObjectWriter(const std::shared_ptr<::Rpc2::Streams::BufferedOutputStream>& stream, const ObjectType& type, const ObjectIdentifier& identifier, const ObjectToken& token)
                    : _stream(stream)
                {
                    WriteValue("", static_cast<std::uint32_t>(type));

                    if (type != ObjectType::Event)
                    {
                        WriteValue("", token);
                    }
                    WriteValue("", identifier);
                }

                ~ObjectWriter()
                {
                    _stream->Flush();
                }

                void WriteValue(const std::string_view&, const std::uint64_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::uint32_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::uint16_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::uint8_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::int64_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::int32_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::int16_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::int8_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const bool& value) override { Write(static_cast<std::uint8_t>(value)); }

                void WriteValue(const std::string_view&, const std::string& value) override
                {
                    Write(static_cast<std::uint64_t>(value.size()));
                    _stream->Write(value.data(), value.size());
                }

                void WriteValue(const std::string_view&, const std::vector<char>& value) override
                {
                    Write(static_cast<std::uint64_t>(value.size())); 
                    _stream->Write(value.data(), value.size());
                }

                std::shared_ptr<IObjectWriter> WriteObject(const std::string_view& identifier) override
                {
                    return shared_from_this();
                }
                std::shared_ptr<IObjectWriter> WriteList(const std::string_view& identifier, const std::size_t length) override
                {
                    Write(static_cast<std::uint32_t>(length));
                    return shared_from_this();
                };

                void Commit() override { _stream->Flush(); }

            private:
                template <typename T>
                void Write(const T& value)
                {
                    _stream->Write(reinterpret_cast<const char*>(&value), sizeof(value));
                }

                std::shared_ptr<::Rpc2::Streams::BufferedOutputStream> _stream;
            };

            class Protocol : public IProtocol
            {
            public:
                virtual ~Protocol() override = default;

                ObjectToken CreateToken() override
                {
                    std::lock_guard<std::mutex> lock(_tokenMutex);
                    auto tokenNumber = _tokenCounter++;
                    return ObjectToken(std::to_string(tokenNumber));
                }

                ObjectType PeekNextObjectType(const std::shared_ptr<Streams::BufferedInputStream>& stream) override
                {
                    ObjectType objectType;
                    stream->Peek(reinterpret_cast<char*>(&objectType), sizeof(ObjectType));
                    return ObjectType::Undefined;
                }

                std::shared_ptr<IObjectWriter> WriteObject(const std::shared_ptr<Streams::BufferedOutputStream>& stream, const ObjectType& type, const ObjectIdentifier& identifier, const ObjectToken& token) override
                {
                    return std::make_shared<ObjectWriter>(stream, type, identifier, token);
                }

                std::shared_ptr<IObjectReader> ReadObject(const std::shared_ptr<Streams::BufferedInputStream>& stream) override
                {
                    auto object = std::make_shared<ObjectReader>(stream);

                    std::uint32_t encodedType = 0;
                    object->ReadValue("", encodedType);
                    object->Type(static_cast<ObjectType>(encodedType));

                    ObjectToken token("");
                    ObjectIdentifier identifier("");

                    if (object->Type() != ObjectType::Event)
                    {
                        object->ReadValue("", token);
                    }
                    
                    object->ReadValue("", identifier);

                    object->Token(token);
                    object->Identifier(identifier);

                    return object;
                }

            private:
                std::mutex _tokenMutex;
                std::uint64_t _tokenCounter;
            };
        }
    }
}