#include "SampleService.hpp"

// This code is generated. It is not recommended to manually manipulate it!
// Generator: NaranjaTool, 0.0.0.3
// 2019-05-28 20:16:00.544425

#include <future>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/utils/Disposer.hpp>

// -------------------------------------------------------------------------------------- DeSerialization Routines



static void Write_SampleService_TransmitStruct_Request(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::Sample::SampleStruct& arg)
{
    
    
{
    auto writer_mdznfhlenj = objectWriter->WriteObject("arg");
writer_mdznfhlenj->WriteValue("arg.Member1", arg.Member1);
writer_mdznfhlenj->WriteValue("arg.Member2", arg.Member2);
}
    
}

static void Read_SampleService_TransmitStruct_Request(naranja::protocol::IObjectReader& objectReader, naranja::generated::Sample::SampleStruct& arg)
{
    
    
{
    auto reader_goepqsmgiy = objectReader->ReadObject("arg");
reader_goepqsmgiy->ReadValue("arg.Member1", arg.Member1);
reader_goepqsmgiy->ReadValue("arg.Member2", arg.Member2);
}
    
}

static void Write_SampleService_TransmitStruct_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitStruct_Response(naranja::protocol::IObjectReader& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitEnum_Request(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::Sample::SampleEnum& arg)
{
    
    
objectWriter->WriteEnum("arg", arg);
    
}

static void Read_SampleService_TransmitEnum_Request(naranja::protocol::IObjectReader& objectReader, naranja::generated::Sample::SampleEnum& arg)
{
    
    
objectReader->ReadEnum("arg", arg);
    
}

static void Write_SampleService_TransmitEnum_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitEnum_Response(naranja::protocol::IObjectReader& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitInteger_Request(naranja::protocol::IObjectWriter& objectWriter, const std::int64_t& arg)
{
    
    
objectWriter->WriteValue("arg", arg);
    
}

static void Read_SampleService_TransmitInteger_Request(naranja::protocol::IObjectReader& objectReader, std::int64_t& arg)
{
    
    
objectReader->ReadValue("arg", arg);
    
}

static void Write_SampleService_TransmitInteger_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitInteger_Response(naranja::protocol::IObjectReader& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitString_Request(naranja::protocol::IObjectWriter& objectWriter, const std::string& arg)
{
    
    
objectWriter->WriteValue("arg", arg);
    
}

static void Read_SampleService_TransmitString_Request(naranja::protocol::IObjectReader& objectReader, std::string& arg)
{
    
    
objectReader->ReadValue("arg", arg);
    
}

static void Write_SampleService_TransmitString_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitString_Response(naranja::protocol::IObjectReader& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitBinary_Request(naranja::protocol::IObjectWriter& objectWriter, const std::vector<char>& arg)
{
    
    
objectWriter->WriteValue("arg", arg);
    
}

static void Read_SampleService_TransmitBinary_Request(naranja::protocol::IObjectReader& objectReader, std::vector<char>& arg)
{
    
    
objectReader->ReadValue("arg", arg);
    
}

static void Write_SampleService_TransmitBinary_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitBinary_Response(naranja::protocol::IObjectReader& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitListOfIntegers_Request(naranja::protocol::IObjectWriter& objectWriter, const std::list<std::int64_t>& arg)
{
    
    
{
    auto writer_ipntibmffb = objectWriter->WriteList("arg", arg.size());
    for (std::size_t i = 0; i < arg.size(); ++i)
    {
        
writer_ipntibmffb->WriteValue("arg[i]", arg[i]);    
    }
}
    
}

static void Read_SampleService_TransmitListOfIntegers_Request(naranja::protocol::IObjectReader& objectReader, std::list<std::int64_t>& arg)
{
    
    
{
    std::size_t size_hthbeikwtt;
    auto reader_wvickclwbq = objectReader->ReadList("arg", size_hthbeikwtt);
    arg.resize(size_hthbeikwtt);
    for (std::size_t i = 0; i < size_hthbeikwtt; ++i)
    {
        
reader_wvickclwbq->ReadValue("arg[i]", arg[i]);    
    }

}
    
}

static void Write_SampleService_TransmitListOfIntegers_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitListOfIntegers_Response(naranja::protocol::IObjectReader& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitListOfStructs_Request(naranja::protocol::IObjectWriter& objectWriter, const std::list<SampleStruct>& arg)
{
    
    
{
    auto writer_irchnfdrth = objectWriter->WriteList("arg", arg.size());
    for (std::size_t i = 0; i < arg.size(); ++i)
    {
        
{
    auto writer_niaedbgphz = writer_irchnfdrth->WriteObject("arg[i]");
writer_niaedbgphz->WriteValue("arg[i].Member1", arg[i].Member1);
writer_niaedbgphz->WriteValue("arg[i].Member2", arg[i].Member2);
}    
    }
}
    
}

static void Read_SampleService_TransmitListOfStructs_Request(naranja::protocol::IObjectReader& objectReader, std::list<SampleStruct>& arg)
{
    
    
{
    std::size_t size_cuxizojwem;
    auto reader_eobdoxndvb = objectReader->ReadList("arg", size_cuxizojwem);
    arg.resize(size_cuxizojwem);
    for (std::size_t i = 0; i < size_cuxizojwem; ++i)
    {
        
{
    auto reader_vnsvqieiqe = reader_eobdoxndvb->ReadObject("arg[i]");
reader_vnsvqieiqe->ReadValue("arg[i].Member1", arg[i].Member1);
reader_vnsvqieiqe->ReadValue("arg[i].Member2", arg[i].Member2);
}    
    }

}
    
}

static void Write_SampleService_TransmitListOfStructs_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitListOfStructs_Response(naranja::protocol::IObjectReader& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_ReceiveStruct_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveStruct_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveStruct_Response(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::Sample::SampleStruct& returnValue)
{
    
    
{
    auto writer_rnusxotzrw = objectWriter->WriteObject("returnValue");
writer_rnusxotzrw->WriteValue("returnValue.Member1", returnValue.Member1);
writer_rnusxotzrw->WriteValue("returnValue.Member2", returnValue.Member2);
}
    
}

static void Read_SampleService_ReceiveStruct_Response(naranja::protocol::IObjectReader& objectReader, naranja::generated::Sample::SampleStruct& returnValue)
{
    
    
{
    auto reader_hhkclllmoa = objectReader->ReadObject("returnValue");
reader_hhkclllmoa->ReadValue("returnValue.Member1", returnValue.Member1);
reader_hhkclllmoa->ReadValue("returnValue.Member2", returnValue.Member2);
}
    
}
static void Write_SampleService_ReceiveEnum_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveEnum_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveEnum_Response(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::Sample::SampleEnum& returnValue)
{
    
    
objectWriter->WriteEnum("returnValue", returnValue);
    
}

static void Read_SampleService_ReceiveEnum_Response(naranja::protocol::IObjectReader& objectReader, naranja::generated::Sample::SampleEnum& returnValue)
{
    
    
objectReader->ReadEnum("returnValue", returnValue);
    
}
static void Write_SampleService_ReceiveInteger_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveInteger_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveInteger_Response(naranja::protocol::IObjectWriter& objectWriter, const std::int64_t& returnValue)
{
    
    
objectWriter->WriteValue("returnValue", returnValue);
    
}

static void Read_SampleService_ReceiveInteger_Response(naranja::protocol::IObjectReader& objectReader, std::int64_t& returnValue)
{
    
    
objectReader->ReadValue("returnValue", returnValue);
    
}
static void Write_SampleService_ReceiveString_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveString_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveString_Response(naranja::protocol::IObjectWriter& objectWriter, const std::string& returnValue)
{
    
    
objectWriter->WriteValue("returnValue", returnValue);
    
}

static void Read_SampleService_ReceiveString_Response(naranja::protocol::IObjectReader& objectReader, std::string& returnValue)
{
    
    
objectReader->ReadValue("returnValue", returnValue);
    
}
static void Write_SampleService_ReceiveBinary_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveBinary_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveBinary_Response(naranja::protocol::IObjectWriter& objectWriter, const std::vector<char>& returnValue)
{
    
    
objectWriter->WriteValue("returnValue", returnValue);
    
}

static void Read_SampleService_ReceiveBinary_Response(naranja::protocol::IObjectReader& objectReader, std::vector<char>& returnValue)
{
    
    
objectReader->ReadValue("returnValue", returnValue);
    
}
static void Write_SampleService_ReceiveListOfIntegers_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveListOfIntegers_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveListOfIntegers_Response(naranja::protocol::IObjectWriter& objectWriter, const std::list<std::int64_t>& returnValue)
{
    
    
{
    auto writer_robryypmie = objectWriter->WriteList("returnValue", returnValue.size());
    for (std::size_t i = 0; i < returnValue.size(); ++i)
    {
        
writer_robryypmie->WriteValue("returnValue[i]", returnValue[i]);    
    }
}
    
}

static void Read_SampleService_ReceiveListOfIntegers_Response(naranja::protocol::IObjectReader& objectReader, std::list<std::int64_t>& returnValue)
{
    
    
{
    std::size_t size_aztdlzdjtx;
    auto reader_zhzhsverpx = objectReader->ReadList("returnValue", size_aztdlzdjtx);
    returnValue.resize(size_aztdlzdjtx);
    for (std::size_t i = 0; i < size_aztdlzdjtx; ++i)
    {
        
reader_zhzhsverpx->ReadValue("returnValue[i]", returnValue[i]);    
    }

}
    
}
static void Write_SampleService_ReceiveListOfStructs_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveListOfStructs_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveListOfStructs_Response(naranja::protocol::IObjectWriter& objectWriter, const std::list<SampleStruct>& returnValue)
{
    
    
{
    auto writer_bcaqjihwgb = objectWriter->WriteList("returnValue", returnValue.size());
    for (std::size_t i = 0; i < returnValue.size(); ++i)
    {
        
{
    auto writer_lmhnkgnsrw = writer_bcaqjihwgb->WriteObject("returnValue[i]");
writer_lmhnkgnsrw->WriteValue("returnValue[i].Member1", returnValue[i].Member1);
writer_lmhnkgnsrw->WriteValue("returnValue[i].Member2", returnValue[i].Member2);
}    
    }
}
    
}

static void Read_SampleService_ReceiveListOfStructs_Response(naranja::protocol::IObjectReader& objectReader, std::list<SampleStruct>& returnValue)
{
    
    
{
    std::size_t size_flrrdqzpmq;
    auto reader_lohyimnamm = objectReader->ReadList("returnValue", size_flrrdqzpmq);
    returnValue.resize(size_flrrdqzpmq);
    for (std::size_t i = 0; i < size_flrrdqzpmq; ++i)
    {
        
{
    auto reader_wpbsclpcbs = reader_lohyimnamm->ReadObject("returnValue[i]");
reader_wpbsclpcbs->ReadValue("returnValue[i].Member1", returnValue[i].Member1);
reader_wpbsclpcbs->ReadValue("returnValue[i].Member2", returnValue[i].Member2);
}    
    }

}
    
}
static void Write_SampleService_CallFailingFunction_Request(naranja::protocol::IObjectWriter& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_CallFailingFunction_Request(naranja::protocol::IObjectReader& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_CallFailingFunction_Response(naranja::protocol::IObjectWriter& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_CallFailingFunction_Response(naranja::protocol::IObjectReader& objectReader)
{
     
    (void)objectReader;
    
}



static void Write_SampleException(naranja::protocol::IObjectWriter& objectWriter, const naranja::generated::Sample::SampleException& ex)
{
    
    
objectWriter->WriteValue("ex.Description", ex.Description);
    
}

static void Read_SampleException(naranja::protocol::IObjectReader& objectReader, naranja::generated::Sample::SampleException& ex)
{
    
    
objectReader->ReadValue("ex.Description", ex.Description);
    
}

// -------------------------------------------------------------------------------------- Client Side Code

naranja::generated::Sample::ClientSideSampleService::ClientSideSampleService(const std::shared_ptr<naranja::rpc::ClientSideConnection>& connection, const std::shared_ptr<naranja::protocol::IProtocol>& protocol)
    : _connection(connection)
    , _protocol(protocol)
{
}


void naranja::generated::Sample::ClientSideSampleService::TransmitStruct(const SampleStruct& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            Read_SampleService_TransmitStruct_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitStruct", token);
    Write_SampleService_TransmitStruct_Request(*objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitEnum(const SampleEnum& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            Read_SampleService_TransmitEnum_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitEnum", token);
    Write_SampleService_TransmitEnum_Request(*objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitInteger(const std::int64_t& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            Read_SampleService_TransmitInteger_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitInteger", token);
    Write_SampleService_TransmitInteger_Request(*objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitString(const std::string& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            Read_SampleService_TransmitString_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitString", token);
    Write_SampleService_TransmitString_Request(*objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitBinary(const std::vector<char>& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            Read_SampleService_TransmitBinary_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitBinary", token);
    Write_SampleService_TransmitBinary_Request(*objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitListOfIntegers(const std::list<std::int64_t>& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            Read_SampleService_TransmitListOfIntegers_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitListOfIntegers", token);
    Write_SampleService_TransmitListOfIntegers_Request(*objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitListOfStructs(const std::list<SampleStruct>& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            Read_SampleService_TransmitListOfStructs_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitListOfStructs", token);
    Write_SampleService_TransmitListOfStructs_Request(*objectWriter_,  arg);

    return future.get();
}

naranja::generated::Sample::SampleStruct naranja::generated::Sample::ClientSideSampleService::ReceiveStruct()
{
    const auto token = _protocol->CreateToken();

    std::promise<SampleStruct> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            SampleStruct result;
            Read_SampleService_ReceiveStruct_Response(*objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveStruct", token);
    Write_SampleService_ReceiveStruct_Request(*objectWriter_);

    return future.get();
}

naranja::generated::Sample::SampleEnum naranja::generated::Sample::ClientSideSampleService::ReceiveEnum()
{
    const auto token = _protocol->CreateToken();

    std::promise<SampleEnum> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            SampleEnum result;
            Read_SampleService_ReceiveEnum_Response(*objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveEnum", token);
    Write_SampleService_ReceiveEnum_Request(*objectWriter_);

    return future.get();
}

std::int64_t naranja::generated::Sample::Cli<kentSideSampleService::ReceiveInteger()
{
    const auto token = _protocol->CreateToken();

    std::promise<std::int64_t> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            std::int64_t result;
            Read_SampleService_ReceiveInteger_Response(*objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveInteger", token);
    Write_SampleService_ReceiveInteger_Request(*objectWriter_);

    return future.get();
}

std::string naranja::generated::Sample::ClientSideSampleService::ReceiveString()
{
    const auto token = _protocol->CreateToken();

    std::promise<std::string> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            std::string result;
            Read_SampleService_ReceiveString_Response(*objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveString", token);
    Write_SampleService_ReceiveString_Request(*objectWriter_);

    return future.get();
}

std::vector<char> naranja::generated::Sample::ClientSideSampleService::ReceiveBinary()
{
    const auto token = _protocol->CreateToken();

    std::promise<std::vector<char>> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            std::vector<char> result;
            Read_SampleService_ReceiveBinary_Response(*objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveBinary", token);
    Write_SampleService_ReceiveBinary_Request(*objectWriter_);

    return future.get();
}

std::list<std::int64_t> naranja::generated::Sample::ClientSideSampleService::ReceiveListOfIntegers()
{
    const auto token = _protocol->CreateToken();

    std::promise<std::list<std::int64_t>> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            std::list<std::int64_t> result;
            Read_SampleService_ReceiveListOfIntegers_Response(*objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveListOfIntegers", token);
    Write_SampleService_ReceiveListOfIntegers_Request(*objectWriter_);

    return future.get();
}

std::list<SampleStruct> naranja::generated::Sample::ClientSideSampleService::ReceiveListOfStructs()
{
    const auto token = _protocol->CreateToken();

    std::promise<std::list<SampleStruct>> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            
            
            std::list<SampleStruct> result;
            Read_SampleService_ReceiveListOfStructs_Response(*objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveListOfStructs", token);
    Write_SampleService_ReceiveListOfStructs_Request(*objectWriter_);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::CallFailingFunction()
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
            
            
            Read_SampleService_CallFailingFunction_Response(*objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.CallFailingFunction", token);
    Write_SampleService_CallFailingFunction_Request(*objectWriter_);

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
    ConnectHandler(connection, "SampleService.TransmitStruct", &ServerSideSampleService::TransmitStruct);
    ConnectHandler(connection, "SampleService.TransmitEnum", &ServerSideSampleService::TransmitEnum);
    ConnectHandler(connection, "SampleService.TransmitInteger", &ServerSideSampleService::TransmitInteger);
    ConnectHandler(connection, "SampleService.TransmitString", &ServerSideSampleService::TransmitString);
    ConnectHandler(connection, "SampleService.TransmitBinary", &ServerSideSampleService::TransmitBinary);
    ConnectHandler(connection, "SampleService.TransmitListOfIntegers", &ServerSideSampleService::TransmitListOfIntegers);
    ConnectHandler(connection, "SampleService.TransmitListOfStructs", &ServerSideSampleService::TransmitListOfStructs);
    ConnectHandler(connection, "SampleService.ReceiveStruct", &ServerSideSampleService::ReceiveStruct);
    ConnectHandler(connection, "SampleService.ReceiveEnum", &ServerSideSampleService::ReceiveEnum);
    ConnectHandler(connection, "SampleService.ReceiveInteger", &ServerSideSampleService::ReceiveInteger);
    ConnectHandler(connection, "SampleService.ReceiveString", &ServerSideSampleService::ReceiveString);
    ConnectHandler(connection, "SampleService.ReceiveBinary", &ServerSideSampleService::ReceiveBinary);
    ConnectHandler(connection, "SampleService.ReceiveListOfIntegers", &ServerSideSampleService::ReceiveListOfIntegers);
    ConnectHandler(connection, "SampleService.ReceiveListOfStructs", &ServerSideSampleService::ReceiveListOfStructs);
    ConnectHandler(connection, "SampleService.CallFailingFunction", &ServerSideSampleService::CallFailingFunction);
    
}


void naranja::generated::Sample::ServerSideSampleService::TransmitStruct(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    SampleStruct arg;
    Read_SampleService_TransmitStruct_Request(object_,  arg);
    try
    {
        _service->TransmitStruct( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitStruct", object_.Token());
        Write_SampleService_TransmitStruct_Response(*responseObject_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitEnum(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    SampleEnum arg;
    Read_SampleService_TransmitEnum_Request(object_,  arg);
    try
    {
        _service->TransmitEnum( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitEnum", object_.Token());
        Write_SampleService_TransmitEnum_Response(*responseObject_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitInteger(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::int64_t arg;
    Read_SampleService_TransmitInteger_Request(object_,  arg);
    try
    {
        _service->TransmitInteger( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitInteger", object_.Token());
        Write_SampleService_TransmitInteger_Response(*responseObject_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitString(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::string arg;
    Read_SampleService_TransmitString_Request(object_,  arg);
    try
    {
        _service->TransmitString( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitString", object_.Token());
        Write_SampleService_TransmitString_Response(*responseObject_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitBinary(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::vector<char> arg;
    Read_SampleService_TransmitBinary_Request(object_,  arg);
    try
    {
        _service->TransmitBinary( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitBinary", object_.Token());
        Write_SampleService_TransmitBinary_Response(*responseObject_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitListOfIntegers(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::list<std::int64_t> arg;
    Read_SampleService_TransmitListOfIntegers_Request(object_,  arg);
    try
    {
        _service->TransmitListOfIntegers( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitListOfIntegers", object_.Token());
        Write_SampleService_TransmitListOfIntegers_Response(*responseObject_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitListOfStructs(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::list<SampleStruct> arg;
    Read_SampleService_TransmitListOfStructs_Request(object_,  arg);
    try
    {
        _service->TransmitListOfStructs( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitListOfStructs", object_.Token());
        Write_SampleService_TransmitListOfStructs_Response(*responseObject_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveStruct(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveStruct_Request(object_);
    try
    {
        auto result_ =_service->ReceiveStruct();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveStruct", object_.Token());
        Write_SampleService_ReceiveStruct_Response(*responseObject_, result_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveEnum(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveEnum_Request(object_);
    try
    {
        auto result_ =_service->ReceiveEnum();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveEnum", object_.Token());
        Write_SampleService_ReceiveEnum_Response(*responseObject_, result_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveInteger(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveInteger_Request(object_);
    try
    {
        auto result_ =_service->ReceiveInteger();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveInteger", object_.Token());
        Write_SampleService_ReceiveInteger_Response(*responseObject_, result_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveString(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveString_Request(object_);
    try
    {
        auto result_ =_service->ReceiveString();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveString", object_.Token());
        Write_SampleService_ReceiveString_Response(*responseObject_, result_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveBinary(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveBinary_Request(object_);
    try
    {
        auto result_ =_service->ReceiveBinary();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveBinary", object_.Token());
        Write_SampleService_ReceiveBinary_Response(*responseObject_, result_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveListOfIntegers(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveListOfIntegers_Request(object_);
    try
    {
        auto result_ =_service->ReceiveListOfIntegers();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveListOfIntegers", object_.Token());
        Write_SampleService_ReceiveListOfIntegers_Response(*responseObject_, result_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveListOfStructs(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveListOfStructs_Request(object_);
    try
    {
        auto result_ =_service->ReceiveListOfStructs();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveListOfStructs", object_.Token());
        Write_SampleService_ReceiveListOfStructs_Response(*responseObject_, result_);
    }
    catch (...)
    {
        throw;
    }
}
void naranja::generated::Sample::ServerSideSampleService::CallFailingFunction(protocol::IObjectReader& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_CallFailingFunction_Request(object_);
    try
    {
        _service->CallFailingFunction();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.CallFailingFunction", object_.Token());
        Write_SampleService_CallFailingFunction_Response(*responseObject_);
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
