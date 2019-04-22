#pragma once

#include <functional>
#include <mutex>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/rpc/IBroker.hpp>
#include <unordered_map>
#include <vector>

namespace naranja
{
    namespace protocol
    {
        class ObjectBroker : public rpc::IBroker
        {
        public:
            explicit ObjectBroker(const std::shared_ptr<IProtocol>& protocol)
                : _protocol(protocol)
            {
            }

            void RegisterFunctionCallHandler(const protocol::ObjectIdentifier& identifier, const std::function<void(const std::shared_ptr<IObjectReader>& objectReader)>& handler)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _functionCalls[identifier] = handler;
            };

            void RegisterFunctionResponseHandler(const protocol::ObjectToken& token, const std::function<void(const std::shared_ptr<IObjectReader>& objectReader)>& handler)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _functionResponses[token] = handler;
            }

            void Process(streams::IBufferedInputStream& inputStream, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream) override;

        private:
            std::mutex _mutex;
            std::shared_ptr<IProtocol> _protocol;

            std::unordered_map<std::string, std::function<void(const std::shared_ptr<IObjectReader>& objectReader)>> _functionCalls;
            std::unordered_map<protocol::ObjectToken, std::function<void(const std::shared_ptr<IObjectReader>& objectReader)>> _functionResponses;

            void HandleFunctionCall(const std::shared_ptr<IObjectReader>& objectReader);
            void HandleFunctionResponse(const std::shared_ptr<IObjectReader>& objectReader);
            void HandleEvent(const std::shared_ptr<IObjectReader>& objectReader);
        };
    }
}