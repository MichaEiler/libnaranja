#pragma once

#include <istream>
#include <memory>
#include <Rpc2/Streams/IInputStream.hpp>

namespace Rpc2
{
    namespace Streams
    {
        class StdInputStream : public IInputStream
        {
        public:
            static std::shared_ptr<StdInputStream> Create(const std::shared_ptr<std::istream>& inputStream)
            {
                return std::shared_ptr<StdInputStream>(new StdInputStream(inputStream));
            }

            explicit StdInputStream(const std::shared_ptr<std::istream>& inputStream)
                : _inputStream(inputStream)
            {

            }
            virtual ~StdInputStream() noexcept override = default;

            std::size_t Read(char *buffer, const std::size_t length) override
            {
                _inputStream->read(buffer, length);
                return _inputStream->gcount();
            }

        private:
            std::shared_ptr<std::istream> _inputStream;
        };
    }
}
