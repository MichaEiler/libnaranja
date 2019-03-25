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
 
            class ObjectWriter : public IObjectWriter, public std::enable_shared_from_this<ObjectWriter>
            {
            public:
                explicit ObjectWriter(const std::shared_ptr<::Rpc2::Streams::BufferedOutputStream>& stream)
                    : _stream(stream)
                {

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

                void Commit() override { }

            private:
                template <typename T>
                void Write(const T& value)
                {
                    _stream->Write(reinterpret_cast<const char*>(&value), sizeof(value));
                }

                std::shared_ptr<::Rpc2::Streams::BufferedOutputStream> _stream;
            };
        }
    }
}