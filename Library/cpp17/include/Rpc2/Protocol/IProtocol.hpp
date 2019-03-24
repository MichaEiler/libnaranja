#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <Rpc2/Streams/BufferedInputStream.hpp>
#include <Rpc2/Streams/BufferedOutputStream.hpp>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

namespace Rpc2
{
    namespace Protocol
    {
        using ObjectToken = std::string;
        using ObjectIdentifier = std::string;

        enum class ObjectType : std::uint32_t
        {
            Undefined = 0,
            FunctionCall = 1,
            FunctionResponse = 2,
            Exception = 3,
            Event = 4
        };
 
        class IObjectWriter
        {
        public:
            virtual ~IObjectWriter() = default;

            virtual void WriteValue(const std::string_view& identifier, const std::uint64_t& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::uint32_t& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::uint16_t& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::uint8_t& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::int64_t& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::int32_t& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::int16_t& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::int8_t& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const bool& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::string& value) = 0;
            virtual void WriteValue(const std::string_view& identifier, const std::vector<char>& value) = 0;

            virtual std::shared_ptr<IObjectWriter> WriteObject(const std::string_view& identifier);
            virtual std::shared_ptr<IObjectWriter> WriteList(const std::string_view& identifier, const std::size_t length);

            virtual void Commit() = 0;
        };

        class IObjectReader
        {
        public:
            virtual ~IObjectReader() = default;

            virtual ObjectToken Token() const = 0;
            virtual ObjectType Type() const = 0;
            virtual ObjectIdentifier Identifier() const = 0;

            virtual void ReadValue(const std::string_view& identifier, std::uint64_t& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::uint32_t& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::uint16_t& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::uint8_t& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::int64_t& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::int32_t& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::int16_t& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::int8_t& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, bool& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::string& value) = 0;
            virtual void ReadValue(const std::string_view& identifier, std::vector<char>& value) = 0;

            virtual std::shared_ptr<IObjectReader> ReadList(const std::string_view& identifier, std::size_t& itemCount) = 0;
            virtual std::shared_ptr<IObjectReader> ReadObject(const std::string_view& identifier) = 0;
        };

        class IProtocol
        {
        public:
            virtual ~IProtocol() = default;

            virtual ObjectToken CreateToken() = 0;
            virtual ObjectType PeekNextObjectType(const std::shared_ptr<Streams::BufferedInputStream>& stream) = 0;

            virtual std::shared_ptr<IObjectWriter> WriteObject(const std::shared_ptr<Streams::BufferedOutputStream>& stream, const ObjectType& type, const ObjectIdentifier& identifier, const ObjectToken& token = ObjectToken());
            virtual std::shared_ptr<IObjectReader> ReadObject(const std::shared_ptr<Streams::BufferedInputStream>& stream);
        };
    }
}