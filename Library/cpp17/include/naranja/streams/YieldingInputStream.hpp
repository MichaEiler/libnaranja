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

            explicit YieldingInputStream(const std::function<void()>& yield, IInputStream& inputStream);

            std::size_t AvailableBytes() const override;
            void Peek(char* buffer, const std::size_t length) override;
            std::size_t TryPeek(char *buffer, const std::size_t length) override;
            void Read(char *buffer, const std::size_t length) override;
            std::size_t TryRead(char *buffer, const std::size_t length) override;

        private:
            std::function<void()> _yield;
            IInputStream& _inputStream;
        };
    }
}