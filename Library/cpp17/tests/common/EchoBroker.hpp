#pragma once

#include <naranja/rpc/IBroker.hpp>
#include <vector>

namespace naranja
{
    namespace tests
    {
        class EchoService : public naranja::rpc::IBroker
        {
        public:
            void Process(naranja::streams::IBufferedInputStream& inputStream, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream) override
            {
                std::vector<char> buffer(1024, 0);
                for (;;)
                {
                    auto availableBytes = inputStream.TryRead(&buffer[0], buffer.size());
                    if (availableBytes == 0)
                    {
                        return;
                    }

                    try
                    { 
                        auto strongOutputStream = outputStream.Lock();
                        
                        strongOutputStream->Write(buffer.data(), availableBytes);
                        strongOutputStream->Flush();
                    } catch(...)
                    {
                        return;
                    }
                }
            }
        };
    }
}