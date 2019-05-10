#include "SampleService.hpp"

#include <future>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/utils/Disposer.hpp>

// -------------------------------------------------------------------------------------- DeSerialization Routines

void naranja::generated::SampleServiceProtocol::Write_FunctionThrowingSampleException_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

void naranja::generated::SampleServiceProtocol::Read_FunctionThrowingSampleException_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

void naranja::generated::SampleServiceProtocol::Write_FunctionThrowingSampleException_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

void naranja::generated::SampleServiceProtocol::Read_FunctionThrowingSampleException_Response(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

void naranja::generated::SampleServiceProtocol::Write_FunctionReturningData_Request(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::SampleEnum& arg1)
{
    objectWriter.WriteValue("arg1", static_cast<std::uint32_t>(arg1));
}

void naranja::generated::SampleServiceProtocol::Read_FunctionReturningData_Request(naranja::protocol::IObjectReader& objectReader, naranja::generated::SampleEnum& result)
{
    std::uint32_t arg1Encoded;
    objectReader.ReadValue("arg1", arg1Encoded);
    result = static_cast<naranja::generated::SampleEnum>(arg1Encoded);
}

void naranja::generated::SampleServiceProtocol::Write_FunctionReturningData_Response(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::SampleStruct& arg1)
{
    objectWriter.WriteValue("arg1.Member1", arg1.Member1);
    objectWriter.WriteValue("arg1.Member2", arg1.Member2);
}

void naranja::generated::SampleServiceProtocol::Read_FunctionReturningData_Response(naranja::protocol::IObjectReader& objectReader, naranja::generated::SampleStruct& result)
{
    objectReader.ReadValue("arg1.Member1", result.Member1);
    objectReader.ReadValue("arg1.Member2", result.Member2);
}

void naranja::generated::SampleServiceProtocol::Write_SampleEvent(protocol::IObjectWriter& objectWriter, const std::string& value)
{
    objectWriter.WriteValue("value", value);
}

void naranja::generated::SampleServiceProtocol::Read_SampleEvent(protocol::IObjectReader& objectReader, std::string& value)
{
    objectReader.ReadValue("value", value);
}

void naranja::generated::SampleServiceProtocol::Write_SampleException(protocol::IObjectWriter& objectWriter, const SampleException& ex)
{
    objectWriter.WriteValue("Description", ex.Description);
}

void naranja::generated::SampleServiceProtocol::Read_SampleException(protocol::IObjectReader& objectReader, SampleException& ex)
{
    objectReader.ReadValue("Description", ex.Description);
}

// -------------------------------------------------------------------------------------- Client Side Code

naranja::generated::ClientSideSampleService::ClientSideSampleService(const std::shared_ptr<naranja::rpc::ClientSideConnection>& connection, const std::shared_ptr<naranja::protocol::IProtocol>& protocol)
    : _connection(connection)
    , _protocol(protocol)
{
    _sampleEventRegistrationDisposer = _connection->RegisterEventHandler("Sample.SampleEvent", [this](const std::shared_ptr<protocol::IObjectReader>& objectReader) {
        std::string value;
        generated::SampleServiceProtocol::Read_SampleEvent(*objectReader, value);

        std::lock_guard<std::mutex> lock(_eventMutex);
        for (auto& listeners : _sampleEventListeners)
        {
            listeners.second(value);
        }
    });
}

void naranja::generated::ClientSideSampleService::FunctionThrowingSampleException()
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "Sample.SampleException")
            {
                generated::SampleException ex;
                generated::SampleServiceProtocol::Read_SampleException(*objectReader, ex);
                throw ex;
            }
            generated::SampleServiceProtocol::Read_FunctionThrowingSampleException_Response(*objectReader);
            promise.set_value();
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto objectWriter = _protocol->WriteObject(*_connection, naranja::protocol::ObjectType::FunctionCall, "Sample.FunctionThrowingSampleException", token);
    generated::SampleServiceProtocol::Write_FunctionThrowingSampleException_Request(*objectWriter);

    future.get();
}

naranja::generated::SampleStruct naranja::generated::ClientSideSampleService::FunctionReturningData(const naranja::generated::SampleEnum& arg1)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    naranja::generated::SampleStruct result;

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise, &result](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            generated::SampleServiceProtocol::Read_FunctionReturningData_Response(*objectReader, result);
            promise.set_value();
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto objectWriter = _protocol->WriteObject(*_connection, naranja::protocol::ObjectType::FunctionCall, "Sample.FunctionReturningData", token);
    generated::SampleServiceProtocol::Write_FunctionReturningData_Request(*objectWriter, arg1);

    future.get();
    return result;
}

naranja::utils::Disposer naranja::generated::ClientSideSampleService::OnSampleEvent(const std::function<void(const std::string&)>& eventHandler)
{
    std::lock_guard<std::mutex> lock(_eventMutex);

    const auto token = _protocol->CreateToken();
    _sampleEventListeners[token] = eventHandler;

    return naranja::utils::Disposer([weakClient = std::weak_ptr<ClientSideSampleService>(shared_from_this()), token](){
        auto client = weakClient.lock();
        if (!client)
        {
            return;
        }

        std::lock_guard<std::mutex> lock(client->_eventMutex);

        auto it = client->_sampleEventListeners.find(token);
        if (it != client->_sampleEventListeners.end())
        {
            client->_sampleEventListeners.erase(it);
        }
    });
}

// -------------------------------------------------------------------------------------- Server Side Code

naranja::generated::ServerSideSampleService::ServerSideSampleService(const std::shared_ptr<ISampleService>& service, const std::shared_ptr<protocol::IProtocol>& protocol)
    : _protocol(protocol)
    , _service(service)
{

}

void naranja::generated::ServerSideSampleService::FunctionThrowingSampleException(protocol::IObjectReader& object, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream)
{
    // TODO: use threadpool
    naranja::generated::SampleServiceProtocol::Read_FunctionThrowingSampleException_Request(object);
    try
    {
        _service->FunctionThrowingSampleException();
        auto reservedOutputStream = outputStream.Lock();
        auto responseObject = _protocol->WriteObject(*reservedOutputStream, naranja::protocol::ObjectType::FunctionResponse, "Sample.FunctionThrowingSampleException", object.Token());
        ::naranja::generated::SampleServiceProtocol::Write_FunctionThrowingSampleException_Response(*responseObject);
    }
    catch(const naranja::generated::SampleException& ex)
    {
        auto reservedOutputStream = outputStream.Lock();
        auto responseObject = _protocol->WriteObject(*reservedOutputStream, naranja::protocol::ObjectType::Exception, "Sample.SampleException", object.Token());
        naranja::generated::SampleServiceProtocol::Write_SampleException(*responseObject, ex);
    }
}

void naranja::generated::ServerSideSampleService::FunctionReturningData(protocol::IObjectReader& object, const utils::LockableResource<streams::IBufferedOutputStream>& outputStream)
{
    // TODO: use threadpool
    naranja::generated::SampleEnum arg1;
    naranja::generated::SampleStruct result;

    naranja::generated::SampleServiceProtocol::Read_FunctionReturningData_Request(object, arg1);
    result = _service->FunctionReturningData(arg1);

    auto reservedOutputStream = outputStream.Lock();
    auto responseObject = _protocol->WriteObject(*reservedOutputStream, naranja::protocol::ObjectType::FunctionResponse, "Sample.FunctionReturningData", object.Token());
    naranja::generated::SampleServiceProtocol::Write_FunctionReturningData_Response(*responseObject, result);
}
