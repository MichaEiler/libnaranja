#pragma once

#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>
#include <Rpc2/Streams/BufferedInputStream.hpp>
#include <Rpc2/Streams/BufferedOutputStream.hpp>
#include <stdexcept>
#include <vector>

namespace Rpc2
{
    namespace Core
    {
        class Connection final : public std::enable_shared_from_this<Connection>
        {
        private:
            std::shared_ptr<Streams::BufferedInputStream> _inputStream;
            std::shared_ptr<Streams::BufferedOutputStream> _outputStream;
            std::mutex _readMutex;
            std::mutex _writeMutex;

            explicit Connection(const std::shared_ptr<Streams::BufferedInputStream>& inputStream, const std::shared_ptr<Streams::BufferedOutputStream>& outputStream)
                : _inputStream(inputStream)
                , _outputStream(outputStream)
            {
            }
        public:
            static std::shared_ptr<Connection> Create(const std::shared_ptr<Streams::BufferedInputStream>& inputStream, const std::shared_ptr<Streams::BufferedOutputStream>& outputStream)
            {
                return std::shared_ptr<Connection>(new Connection(inputStream, outputStream));
            }

            ~Connection() = default;

            std::shared_ptr<Streams::BufferedInputStream> LockInputStream()
            {
                std::unique_lock<std::mutex> lock(_readMutex);
                return std::shared_ptr<Streams::BufferedInputStream>(_inputStream.get(), [connection=shared_from_this(), capturedLock=std::move(lock)](auto *ptr) mutable {
                    capturedLock.unlock();
                });
            }

            std::shared_ptr<Streams::BufferedOutputStream> LockOutputStream()
            {
                std::unique_lock<std::mutex> lock(_writeMutex);
                return std::shared_ptr<Streams::BufferedOutputStream>(_outputStream.get(), [connection=shared_from_this(), capturedLock=std::move(lock)](auto *ptr) mutable {
                    capturedLock.unlock();
                });
            }
        };
    }
}
