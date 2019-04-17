#pragma once

#include <naranja/rpc/IService.hpp>
#include <vector>

namespace naranja
{
    namespace tests
    {
        class EchoService : public naranja::rpc::IService
        {
        public:
            void Process(naranja::streams::IBufferedInputStream& inputStream, const std::weak_ptr<naranja::streams::IBufferedOutputStream>& outputStream) override
            {
                std::vector<char> buffer(1024, 0);
                for (;;)
                {
                    auto availableBytes = inputStream.TryRead(&buffer[0], buffer.size());
                    if (availableBytes == 0)
                    {
                        return;
                    }
                    
                    auto strongOutputStream = outputStream.lock();
                    if (!strongOutputStream)
                        return;

                    strongOutputStream->Write(buffer.data(), availableBytes);
                    strongOutputStream->Flush();
                }
            }
        };
    }
}