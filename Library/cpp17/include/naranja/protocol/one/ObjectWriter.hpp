#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <naranja/protocol/IProtocol.hpp>
#include <string>

namespace naranja
{
    namespace protocol
    {
        namespace one
        {
 
            class ObjectWriter : public IObjectWriter, public std::enable_shared_from_this<ObjectWriter>
            {
            public:
                explicit ObjectWriter(::naranja::streams::IBufferedOutputStream& stream);
                ~ObjectWriter();

                void WriteValue(const std::string_view&, const std::uint64_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::uint32_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::uint16_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::uint8_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::int64_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::int32_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::int16_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const std::int8_t& value) override { Write(value); }
                void WriteValue(const std::string_view&, const double& value) override { Write(value); }
                void WriteValue(const std::string_view&, const float& value) override { Write(value); }
                void WriteValue(const std::string_view&, const bool& value) override { Write(static_cast<std::uint8_t>(value)); }
                void WriteValue(const std::string_view&, const std::string& value) override;
                void WriteValue(const std::string_view&, const std::vector<char>& value) override;
                void WriteEnum(const std::string_view& identifier, const std::uint32_t& enumValue) override { WriteValue(identifier, enumValue); }

                std::shared_ptr<IObjectWriter> WriteObject(const std::string_view& identifier) override;
                std::shared_ptr<IObjectWriter> WriteList(const std::string_view& identifier, const std::size_t length) override;

                void Commit() override { }

            private:
                template <typename T>
                void Write(const T& value)
                {
                    _stream.Write(reinterpret_cast<const char*>(&value), sizeof(value));
                }

                ::naranja::streams::IBufferedOutputStream& _stream;
            };
        }
    }
}