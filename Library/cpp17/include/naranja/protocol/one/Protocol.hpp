#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <naranja/protocol/IProtocol.hpp>
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
                
                std::shared_ptr<IObjectWriter> WriteObject(streams::IBufferedOutputStream& stream, const ObjectType& type, const ObjectIdentifier& identifier, const ObjectToken& token) const override;
                std::shared_ptr<IObjectReader> ReadObject(streams::IBufferedInputStream& stream) const override;

            private:
                std::mutex _tokenMutex;
                std::uint32_t _tokenCounter;
            };
        }
    }
}