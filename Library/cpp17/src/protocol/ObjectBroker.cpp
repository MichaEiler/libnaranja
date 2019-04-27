#include "naranja/protocol/ObjectBroker.hpp"

void naranja::protocol::ObjectBroker::Process(streams::IBufferedInputStream& inputStream, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream)
{
    for (;;)
    {
        const auto nextObject = _protocol->ReadObject(inputStream);
        
        switch(nextObject->Type())
        {
        case ObjectType::FunctionCall:
            HandleFunctionCall(nextObject);
            break;
        case ObjectType::FunctionResponse:
            [[fallthrough]];
        case ObjectType::Exception:
            HandleFunctionResponse(nextObject);
            return;
        case ObjectType::Event:
            HandleEvent(nextObject);
            break;
        default:
            throw core::ParseFailureException("Unknown object type.");
        }
    }
}

void naranja::protocol::ObjectBroker::HandleFunctionCall(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    decltype(_functionCalls)::mapped_type handler;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto it = _functionCalls.find(objectReader->Identifier());
        if (it == _functionCalls.end())
        {
            throw core::ParseFailureException("Unknown identifier.");
        }
        handler = it->second;
    }
    handler(objectReader);
}

void naranja::protocol::ObjectBroker::HandleFunctionResponse(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    decltype(_functionResponses)::mapped_type handler;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto it = _functionResponses.find(objectReader->Token());
        if (it == _functionResponses.end())
        {
            throw core::ParseFailureException("No handler registered for received token.");
        }
        handler = it->second;
        _functionResponses.erase(it);
    }
    handler(objectReader);
}

void naranja::protocol::ObjectBroker::HandleEvent(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{

}

