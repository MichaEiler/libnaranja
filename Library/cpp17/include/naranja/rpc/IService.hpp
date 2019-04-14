#pragma once

#include <memory>
#include <naranja/streams/IBufferedInputStream.hpp>
#include <naranja/streams/IBufferedOutputStream.hpp>

namespace naranja
{
    namespace rpc
    {
        class IService
        {
        public:
            virtual ~IService() = default;

            virtual void Process(streams::IBufferedInputStream& inputStream, const std::weak_ptr<streams::IBufferedOutputStream>& outputStream) = 0;
        };
    }
}