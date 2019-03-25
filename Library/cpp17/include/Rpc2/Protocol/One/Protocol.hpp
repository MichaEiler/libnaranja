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
            class Protocol : public IProtocol
            {
            public:
                explicit Protocol() = default;
                virtual ~Protocol() override = default;

                ObjectToken CreateToken() override;
                ObjectToken PeekNextToken(const std::shared_ptr<Streams::BufferedInputStream>& stream) override;
                ObjectType  PeekNextObjectType(const std::shared_ptr<Streams::BufferedInputStream>& stream) override;

                std::shared_ptr<IObjectWriter> WriteObject(const std::shared_ptr<Streams::BufferedOutputStream>& stream, const ObjectType& type, const ObjectIdentifier& identifier, const ObjectToken& token) override;
                std::shared_ptr<IObjectReader> ReadObject(const std::shared_ptr<Streams::BufferedInputStream>& stream) override;

            private:
                std::mutex _tokenMutex;
                std::uint32_t _tokenCounter;
            };
        }
    }
}