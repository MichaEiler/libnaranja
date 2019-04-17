#pragma once

#include <naranja/core/Exceptions.hpp>
#include <naranja/streams/IBufferedOutputStream.hpp>
#include <naranja/streams/IBufferedInputStream.hpp>

namespace naranja
{
    namespace tests
    {
        class BufferedOutputStream : public streams::IBufferedOutputStream
        {
        public:
            explicit BufferedOutputStream(streams::IOutputStream& outputStream)
                : _stream(outputStream)
            {
                
            }

            void Write(const char* buffer, const std::size_t length) override { _stream.Write(buffer, length); }
            void Flush() override { }

        private:
            streams::IOutputStream& _stream;
        };

        class BufferedInputStream : public streams::IBufferedInputStream
        {
        public:
            explicit BufferedInputStream(streams::IInputStream& inputStream)
                : _stream(inputStream)
            {
                
            }
            
            std::size_t AvailableBytes() const override { return _stream.AvailableBytes(); }

            void Read(char* buffer, const std::size_t length) override
            {
                const auto receivedBytes = _stream.TryRead(buffer, length);
                if (receivedBytes != length)
                {
                    throw naranja::exceptions::StreamClosed();
                }
            }

            void Peek(char* buffer, const std::size_t length) override
            {
                const auto receivedBytes = _stream.TryPeek(buffer, length);
                if (receivedBytes != length)
                {
                    throw naranja::exceptions::StreamClosed();
                }
            }

        private:
            streams::IInputStream& _stream;
        };
    }
}
