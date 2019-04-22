#pragma once

#include <memory>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/streams/IBufferedInputStream.hpp>
#include <naranja/streams/IBufferedOutputStream.hpp>
#include <naranja/utils/LockableResource.hpp>

namespace naranja
{
    namespace rpc
    {
        class IBroker
        {
        public:
            virtual ~IBroker() = default;

            virtual void Process(streams::IBufferedInputStream& inputStream, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream) = 0;
        };
    }
}