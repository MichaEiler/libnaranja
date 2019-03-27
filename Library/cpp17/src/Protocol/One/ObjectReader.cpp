#include "Rpc2/Protocol/One/ObjectReader.hpp"

Rpc2::Protocol::One::ObjectReader::ObjectReader(const std::shared_ptr<::Rpc2::Streams::BufferedInputStream>& stream)
    : _stream(stream)
{
}

void Rpc2::Protocol::One::ObjectReader::ReadValue(const std::string_view&, bool& value)
{
    std::uint8_t encodedValue = 0;
    Read(encodedValue);
    value = encodedValue != 0;
}

void Rpc2::Protocol::One::ObjectReader::ReadValue(const std::string_view&, std::string& value)
{
    std::uint64_t length = 0;
    Read(length);
    value.resize(length);
    _stream->Read(&value[0], value.size());
}

void Rpc2::Protocol::One::ObjectReader::ReadValue(const std::string_view&, std::vector<char>& value)
{
    std::uint64_t length = 0;
    Read(length);
    value.resize(length);
    _stream->Read(&value[0], value.size());
}

std::shared_ptr<Rpc2::Protocol::IObjectReader> Rpc2::Protocol::One::ObjectReader::ReadList(const std::string_view&, std::size_t& itemCount)
{
    std::uint32_t itemCountInt = 0;
    Read(itemCountInt);
    itemCount = static_cast<std::size_t>(itemCountInt);
    return shared_from_this();
}

std::shared_ptr<Rpc2::Protocol::IObjectReader> Rpc2::Protocol::One::ObjectReader::ReadObject(const std::string_view&)
{
    return shared_from_this();
}