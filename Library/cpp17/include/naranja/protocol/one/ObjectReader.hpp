#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/streams/BufferedOutputStream.hpp>
#include <string>

namespace naranja
{
    namespace protocol
    {
        namespace one
        {
            class ObjectReader : public IObjectReader, public std::enable_shared_from_this<ObjectReader>
            {
            public:
                explicit ObjectReader(const std::shared_ptr<::naranja::streams::BufferedInputStream>& stream);

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
                void ReadValue(const std::string_view&, bool& value) override;
                void ReadValue(const std::string_view&, std::string& value) override;
                void ReadValue(const std::string_view&, std::vector<char>& value) override;

                std::shared_ptr<IObjectReader> ReadList(const std::string_view&, std::size_t& itemCount) override;
                std::shared_ptr<IObjectReader> ReadObject(const std::string_view&) override;

            private:
                template <typename T>
                void Read(T& value)
                {
                    _stream->Read(reinterpret_cast<char*>(&value), sizeof(T));
                }

                ObjectIdentifier _identifier;
                ObjectToken _token;
                ObjectType _type;

                std::shared_ptr<naranja::streams::BufferedInputStream> _stream;
            };
        }
    }
}
