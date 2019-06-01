#include "naranja/protocol/one/ObjectWriter.hpp"

naranja::protocol::one::ObjectWriter::ObjectWriter(::naranja::streams::IBufferedOutputStream& stream)
    : _stream(stream)
{

}

naranja::protocol::one::ObjectWriter::~ObjectWriter()
{
    _stream.Flush();
}

void naranja::protocol::one::ObjectWriter::WriteValue(const std::string_view&, const std::string& value)
{
    Write(static_cast<std::uint64_t>(value.size()));
    _stream.Write(value.data(), value.size());
}

void naranja::protocol::one::ObjectWriter::WriteValue(const std::string_view&, const std::vector<char>& value)
{
    Write(static_cast<std::uint64_t>(value.size())); 
    _stream.Write(value.data(), value.size());
}

std::shared_ptr<naranja::protocol::IObjectWriter> naranja::protocol::one::ObjectWriter::WriteObject(const std::string_view&)
{
    return shared_from_this();
}

std::shared_ptr<naranja::protocol::IObjectWriter> naranja::protocol::one::ObjectWriter::WriteList(const std::string_view&, const std::size_t length)
{
    Write(static_cast<std::uint32_t>(length));
    return shared_from_this();
}