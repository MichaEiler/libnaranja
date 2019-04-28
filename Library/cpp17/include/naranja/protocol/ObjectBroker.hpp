#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/rpc/IBroker.hpp>
#include <naranja/utils/Disposer.hpp>
#include <unordered_map>
#include <vector>

namespace naranja
{
    namespace protocol
    {
        class ObjectBroker : public rpc::IBroker, public std::enable_shared_from_this<ObjectBroker>
        {
        public:
            static std::shared_ptr<ObjectBroker> Create(const std::shared_ptr<IProtocol>& protocol)
            {
                return std::make_shared<ObjectBroker>(protocol);
            }

            naranja::utils::Disposer RegisterFunctionCallHandler(const protocol::ObjectIdentifier& identifier, const std::function<void(const std::shared_ptr<IObjectReader>& objectReader)>& handler)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _functionCalls[identifier] = handler;

                return naranja::utils::Disposer([weakBroker = std::weak_ptr<ObjectBroker>(shared_from_this()), identifier](){
                    auto strongBroker = weakBroker.lock();
                    if (!strongBroker)
                    {
                        return;
                    }

                    std::lock_guard<std::mutex> lock(strongBroker->_mutex);

                    auto it = strongBroker->_functionCalls.find(identifier);
                    if (it != strongBroker->_functionCalls.end())
                    {
                        strongBroker->_functionCalls.erase(identifier);
                    }
                });
            };

            naranja::utils::Disposer RegisterFunctionResponseHandler(const protocol::ObjectToken& token, const std::function<void(const std::shared_ptr<IObjectReader>& objectReader)>& handler)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _functionResponses[token] = handler;

                return naranja::utils::Disposer([weakBroker = std::weak_ptr<ObjectBroker>(shared_from_this()), token](){
                    auto strongBroker = weakBroker.lock();
                    if (!strongBroker)
                    {
                        return;
                    }

                    std::lock_guard<std::mutex> lock(strongBroker->_mutex);

                    auto it = strongBroker->_functionResponses.find(token);
                    if (it != strongBroker->_functionResponses.end())
                    {
                        strongBroker->_functionResponses.erase(token);
                    }
                });
            }

            naranja::utils::Disposer RegisterEventHandler(const protocol::ObjectIdentifier& identifier, const std::function<void(const std::shared_ptr<IObjectReader>& objectReader)>& handler)
            {
                // On the client side the behavior for events is the same as for functions on the server side.
                return RegisterFunctionCallHandler(identifier, handler);
            }

            void Process(streams::IBufferedInputStream& inputStream, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream) override;

        private:
            explicit ObjectBroker(const std::shared_ptr<IProtocol>& protocol)
                : _protocol(protocol)
            {
            }

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