#pragma once

#include <memory>
#include <ostream>
#include <Rpc2/Streams/IOutputStream.hpp>

namespace Rpc2
{
    namespace Streams
    {
        class StdOutputStream : public IOutputStream
        {
        public:
            static std::shared_ptr<StdOutputStream> Create(const std::shared_ptr<std::ostream>& outputStream)
            {
                return std::shared_ptr<StdOutputStream>(new StdOutputStream(outputStream));
            }

            explicit StdOutputStream(const std::shared_ptr<std::ostream>& outputStream)
                : _outputStream(outputStream)
            {

            }
            virtual ~StdOutputStream() noexcept override = default;

            void Write(const char* buffer, const std::size_t length) override
            {
                _outputStream->write(buffer, length);   
            }

        private:
            std::shared_ptr<std::ostream> _outputStream;
        };
    }
}
