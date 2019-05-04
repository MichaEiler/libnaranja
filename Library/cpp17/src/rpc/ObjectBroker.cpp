#include "naranja/rpc/ObjectBroker.hpp"

void naranja::rpc::ObjectBroker::Process(streams::IBufferedInputStream& inputStream, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream)
{
    for (;;)
    {
        const auto nextObject = _protocol->ReadObject(inputStream);
        
        switch(nextObject->Type())
        {
        case naranja::protocol::ObjectType::FunctionCall:
            HandleFunctionCall(nextObject, outputStream);
            break;
        case naranja::protocol::ObjectType::FunctionResponse:
            [[fallthrough]];
        case naranja::protocol::ObjectType::Exception:
            HandleFunctionResponse(nextObject);
            return;
        case naranja::protocol::ObjectType::Event:
            HandleEvent(nextObject);
            break;
        default:
            throw core::ParseFailureException("Unknown object type.");
        }
    }
}

void naranja::rpc::ObjectBroker::HandleFunctionCall(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream)
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
    handler(objectReader, outputStream);
}

void naranja::rpc::ObjectBroker::HandleFunctionResponse(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
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

void naranja::rpc::ObjectBroker::HandleEvent(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    decltype(_events)::mapped_type handler;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto it = _events.find(objectReader->Identifier());
        if (it == _events.end())
        {
            throw core::ParseFailureException("Unknown identifier.");
        }
        handler = it->second;
    }
    handler(objectReader);
}

