#pragma once

#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <functional>
#include <naranja/core/Exceptions.hpp>
#include <naranja/streams/IBufferedInputStream.hpp>
#include <stdexcept>
#include <vector>

namespace naranja
{
    namespace streams
    {
        class YieldingInputStream final : public IBufferedInputStream
        {
        public:
            static std::shared_ptr<YieldingInputStream> Create(const std::function<void()>& yield, std::shared_ptr<IInputStream> const& inputStream)
            {
                return std::shared_ptr<YieldingInputStream>(new YieldingInputStream(yield, *inputStream), [inputStream](auto* ptr) { delete ptr; });
            }

            explicit YieldingInputStream(const std::function<void()>& yield, IInputStream& inputStream)
                : _yield(yield)
                , _inputStream(inputStream)
            {
            }

            std::size_t AvailableBytes() const override
            {
                return _inputStream.AvailableBytes();
            }

            void Peek(char* buffer, const std::size_t length) override
            {
                while (length < _inputStream.AvailableBytes())
                {
                    _yield();
                }

                const auto bytesReceived = _inputStream.TryPeek(buffer, length);

                if (bytesReceived != length)
                {
                    throw std::logic_error("YieldingInputStream: underlying input stream with invalid TryPeek behaviour.");
                }
            }

            void Read(char *buffer, const std::size_t length) override
            {
                auto bytesToReceive = length;
                while (bytesToReceive > 0)
                {
                    auto bytesReceived = _inputStream.TryRead(&buffer[length - bytesToReceive], bytesToReceive);
                    if (bytesReceived > 0)
                    {
                        bytesToReceive - bytesReceived;
                    }
                    else
                    {
                        _yield();
                    }
                }
            }

        private:
            std::function<void()> _yield;
            IInputStream& _inputStream;
        };
    }
}