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
            class Protocol : public IProtocol
            {
            public:
                explicit Protocol() = default;
                virtual ~Protocol() override = default;

                ObjectToken CreateToken() override;
                ObjectToken PeekNextToken(const std::shared_ptr<streams::BufferedInputStream>& stream) override;
                ObjectType  PeekNextObjectType(const std::shared_ptr<streams::BufferedInputStream>& stream) override;

                std::shared_ptr<IObjectWriter> WriteObject(const std::shared_ptr<streams::BufferedOutputStream>& stream, const ObjectType& type, const ObjectIdentifier& identifier, const ObjectToken& token) override;
                std::shared_ptr<IObjectReader> ReadObject(const std::shared_ptr<streams::BufferedInputStream>& stream) override;

            private:
                std::mutex _tokenMutex;
                std::uint32_t _tokenCounter;
            };
        }
    }
}