#pragma once

#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <Rpc2/Core/Connection.hpp>
#include <Rpc2/Core/Types.hpp>
#include <unordered_map>

namespace Rpc2
{
    namespace Core
    {
        class Client
        {
        public:
            explicit Client(const std::shared_ptr<Core::Connection>& connection)
                : _connection(connection) {

            }

            std::future<void> EnqueueResponseHandler(const Core::MessageToken token, const std::function<void(const std::shared_ptr<Streams::BufferedInputStream>&)>& func)
            {
                std::lock_guard<std::mutex> lock(_clientMutex);
                _reponseHandlerMap[token] = ResponseHandler{ {}, func };
                return _reponseHandlerMap[token]._promise.get_future();
            }

            void Run()
            {
                std::unique_lock<std::mutex> lock(_clientMutex);

                while (!_shutdownInitiated)
                {
                    
                }
            }

        private:
            bool _shutdownInitiated = false;

            std::shared_ptr<Core::Connection> _connection;
            std::mutex _clientMutex;

            struct ResponseHandler
            {
                std::promise<void> _promise;
                std::function<void(const std::shared_ptr<Streams::BufferedInputStream>&)> _readResponse;
            };

            std::unordered_map<Core::MessageToken, ResponseHandler> _reponseHandlerMap;
        };
    }
}