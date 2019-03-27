#include "Rpc2/Protocol/One/ObjectWriter.hpp"

Rpc2::Protocol::One::ObjectWriter::ObjectWriter(const std::shared_ptr<::Rpc2::Streams::BufferedOutputStream>& stream)
    : _stream(stream)
{

}

Rpc2::Protocol::One::ObjectWriter::~ObjectWriter()
{
    _stream->Flush();
}

void Rpc2::Protocol::One::ObjectWriter::WriteValue(const std::string_view&, const std::string& value)
{
    Write(static_cast<std::uint64_t>(value.size()));
    _stream->Write(value.data(), value.size());
}

void Rpc2::Protocol::One::ObjectWriter::WriteValue(const std::string_view&, const std::vector<char>& value)
{
    Write(static_cast<std::uint64_t>(value.size())); 
    _stream->Write(value.data(), value.size());
}

std::shared_ptr<Rpc2::Protocol::IObjectWriter> Rpc2::Protocol::One::ObjectWriter::WriteObject(const std::string_view& identifier)
{
    return shared_from_this();
}

std::shared_ptr<Rpc2::Protocol::IObjectWriter> Rpc2::Protocol::One::ObjectWriter::WriteList(const std::string_view& identifier, const std::size_t length)
{
    Write(static_cast<std::uint32_t>(length));
    return shared_from_this();
}