#include "SampleService.hpp"

// This code is generated. It is not recommended to manually manipulate it!
// Generator: NaranjaTool, 0.0.0.3
// 2019-05-14 22:20:36.137431

#include <future>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/utils/Disposer.hpp>

// -------------------------------------------------------------------------------------- DeSerialization Routines



static void Write_SampleService_FunctionThrowingSampleException_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_FunctionThrowingSampleException_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_FunctionThrowingSampleException_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_FunctionThrowingSampleException_Response(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}
static void Write_SampleService_FunctionReturningData_Request(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::Sample::SampleEnum&arg1)
{
    (void)objectWriter;
}

static void Read_SampleService_FunctionReturningData_Request(naranja::protocol::IObjectReader& objectReader, naranja::generated::Sample::SampleEnum&arg1)
{
    (void)objectReader;
}

static void Write_SampleService_FunctionReturningData_Response(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::Sample::SampleStruct& returnValue)
{
    (void)objectWriter;
}

static void Read_SampleService_FunctionReturningData_Response(naranja::protocol::IObjectReader& objectReader, naranja::generated::Sample::SampleStruct& returnValue)
{
    (void)objectReader;
}



static void Write_SampleException(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::Sample::SampleException& ex)
{

}

static void Read_SampleException(naranja::protocol::IObjectReader& objectReader, naranja::generated::Sample::SampleException& ex)
{

}

// -------------------------------------------------------------------------------------- Client Side Code

naranja::generated::Sample::ClientSideSampleService::ClientSideSampleService(const std::shared_ptr<naranja::rpc::ClientSideConnection>& connection, const std::shared_ptr<naranja::protocol::IProtocol>& protocol)
    : _connection(connection)
    , _protocol(protocol)
{
}


void naranja::generated::Sample::ClientSideSampleService::FunctionThrowingSampleException()
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            if (objectReader->Identifier() == "SampleService.SampleException")
            {
                generated::Sample::SampleException ex;
                Read_SampleException(*objectReader, ex);
                throw ex;
            }
            
            
            Read_SampleService_FunctionThrowingSampleException_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream = _connection->ReserveOutputStream();
    auto objectWriter = _protocol->WriteObject(*outputStream, naranja::protocol::ObjectType::FunctionCall, "SampleService.FunctionThrowingSampleException", token);
    Write_SampleService_FunctionThrowingSampleException_Request(*objectWriter);

    return future.get();
}

naranja::generated::Sample::SampleStruct naranja::generated::Sample::ClientSideSampleService::FunctionReturningData(const SampleEnum&arg1)
{
    const auto token = _protocol->CreateToken();

    std::promise<SampleStruct> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            SampleStruct result;
            Read_SampleService_FunctionReturningData_Response(*objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream = _connection->ReserveOutputStream();
    auto objectWriter = _protocol->WriteObject(*outputStream, naranja::protocol::ObjectType::FunctionCall, "SampleService.FunctionReturningData", token);
    Write_SampleService_FunctionReturningData_Request(*objectWriter, arg1);

    return future.get();
}


// -------------------------------------------------------------------------------------- Server Side Code

naranja::generated::Sample::ServerSideSampleService::ServerSideSampleService(const std::shared_ptr<ISampleService>& service, const std::shared_ptr<protocol::IProtocol>& protocol)
    : _protocol(protocol)
    , _service(service)
{

}

void naranja::generated::Sample::ServerSideSampleService::RegisterNewConnection(const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection)
{
    ConnectHandler(connection, "SampleService.FunctionThrowingSampleException", &ServerSideSampleService::FunctionThrowingSampleException);
    ConnectHandler(connection, "SampleService.FunctionReturningData", &ServerSideSampleService::FunctionReturningData);
    
}


void naranja::generated::Sample::ServerSideSampleService::FunctionThrowingSampleException(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_FunctionThrowingSampleException_Request(object_);
    try
    {
        _service->FunctionThrowingSampleException();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.FunctionThrowingSampleException", object_.Token());
        Write_SampleService_FunctionThrowingSampleException_Response(*responseObject_);
    }
    catch (const naranja::generated::Sample::SampleException& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "Sample.SampleException", object_.Token());
        Write_SampleException(*responseObject_, ex);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::FunctionReturningData(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    SampleEnum arg1;
    Read_SampleService_FunctionReturningData_Request(object_, arg1);
    try
    {
        auto result_ =_service->FunctionReturningData(arg1);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.FunctionReturningData", object_.Token());
        Write_SampleService_FunctionReturningData_Response(*responseObject_, result_);
    }
    catch (...)
    {
        throw;
    }
}
