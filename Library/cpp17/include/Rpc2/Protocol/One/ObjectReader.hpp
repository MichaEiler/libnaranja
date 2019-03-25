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
        }
    }
}