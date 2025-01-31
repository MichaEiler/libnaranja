#include "Sample.hpp"

// This code is generated. It is not recommended to manually manipulate it!
// Generator: NaranjaTool, 0.0.0.3
// 2020-02-07 13:16:52.267757

#include <future>
#include <naranja/protocol/IProtocol.hpp>
#include <naranja/utils/Disposer.hpp>

// -------------------------------------------------------------------------------------- DeSerialization Routines



static void Write_SampleService_TransmitStruct_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const naranja::generated::Sample::SampleStruct& arg)
{
    
    
{
    auto writer_csekqvmipu = objectWriter->WriteObject("arg");
writer_csekqvmipu->WriteValue("arg.Member1", arg.Member1);
writer_csekqvmipu->WriteValue("arg.Member2", arg.Member2);
}
    
}

static void Read_SampleService_TransmitStruct_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, naranja::generated::Sample::SampleStruct& arg)
{
    
    
{
    auto reader_ctguskcela = objectReader->ReadObject("arg");
reader_ctguskcela->ReadValue("arg.Member1", arg.Member1);
reader_ctguskcela->ReadValue("arg.Member2", arg.Member2);
}
    
}

static void Write_SampleService_TransmitStruct_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitStruct_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitEnum_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const naranja::generated::Sample::SampleEnum& arg)
{
    
    
objectWriter->WriteEnum("arg", arg);
    
}

static void Read_SampleService_TransmitEnum_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, naranja::generated::Sample::SampleEnum& arg)
{
    
    
arg = objectReader->ReadEnum<std::remove_reference<decltype(arg)>::type>("arg");
    
}

static void Write_SampleService_TransmitEnum_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitEnum_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitInteger_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::int64_t& arg)
{
    
    
objectWriter->WriteValue("arg", arg);
    
}

static void Read_SampleService_TransmitInteger_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::int64_t& arg)
{
    
    
objectReader->ReadValue("arg", arg);
    
}

static void Write_SampleService_TransmitInteger_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitInteger_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitString_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::string& arg)
{
    
    
objectWriter->WriteValue("arg", arg);
    
}

static void Read_SampleService_TransmitString_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::string& arg)
{
    
    
objectReader->ReadValue("arg", arg);
    
}

static void Write_SampleService_TransmitString_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitString_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitBinary_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::vector<char>& arg)
{
    
    
objectWriter->WriteValue("arg", arg);
    
}

static void Read_SampleService_TransmitBinary_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::vector<char>& arg)
{
    
    
objectReader->ReadValue("arg", arg);
    
}

static void Write_SampleService_TransmitBinary_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitBinary_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitListOfIntegers_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::vector<std::int64_t>& arg)
{
    
    
{
    auto writer_dksukvozox = objectWriter->WriteList("arg", arg.size());
    for (std::size_t i = 0; i < arg.size(); ++i)
    {
        
writer_dksukvozox->WriteValue("arg[i]", arg[i]);    
    }
}
    
}

static void Read_SampleService_TransmitListOfIntegers_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::vector<std::int64_t>& arg)
{
    
    
{
    std::size_t size_jnsegglbri;
    auto reader_tundfrfhis = objectReader->ReadList("arg", size_jnsegglbri);
    arg.resize(size_jnsegglbri);
    for (std::size_t i = 0; i < size_jnsegglbri; ++i)
    {
        
reader_tundfrfhis->ReadValue("arg[i]", arg[i]);    
    }

}
    
}

static void Write_SampleService_TransmitListOfIntegers_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitListOfIntegers_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_TransmitListOfStructs_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::vector<naranja::generated::Sample::SampleStruct>& arg)
{
    
    
{
    auto writer_fevnvlscxj = objectWriter->WriteList("arg", arg.size());
    for (std::size_t i = 0; i < arg.size(); ++i)
    {
        
{
    auto writer_ytfoekefdv = writer_fevnvlscxj->WriteObject("arg[i]");
writer_ytfoekefdv->WriteValue("arg[i].Member1", arg[i].Member1);
writer_ytfoekefdv->WriteValue("arg[i].Member2", arg[i].Member2);
}    
    }
}
    
}

static void Read_SampleService_TransmitListOfStructs_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::vector<naranja::generated::Sample::SampleStruct>& arg)
{
    
    
{
    std::size_t size_teokmecydw;
    auto reader_wzxiwxqyel = objectReader->ReadList("arg", size_teokmecydw);
    arg.resize(size_teokmecydw);
    for (std::size_t i = 0; i < size_teokmecydw; ++i)
    {
        
{
    auto reader_uqdacdidxo = reader_wzxiwxqyel->ReadObject("arg[i]");
reader_uqdacdidxo->ReadValue("arg[i].Member1", arg[i].Member1);
reader_uqdacdidxo->ReadValue("arg[i].Member2", arg[i].Member2);
}    
    }

}
    
}

static void Write_SampleService_TransmitListOfStructs_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_TransmitListOfStructs_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
     
    (void)objectReader;
    
}
static void Write_SampleService_ReceiveStruct_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveStruct_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveStruct_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const naranja::generated::Sample::SampleStruct& returnValue)
{
    
    
{
    auto writer_ugqgsnkzqo = objectWriter->WriteObject("returnValue");
writer_ugqgsnkzqo->WriteValue("returnValue.Member1", returnValue.Member1);
writer_ugqgsnkzqo->WriteValue("returnValue.Member2", returnValue.Member2);
}
    
}

static void Read_SampleService_ReceiveStruct_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, naranja::generated::Sample::SampleStruct& returnValue)
{
    
    
{
    auto reader_eowkwedtet = objectReader->ReadObject("returnValue");
reader_eowkwedtet->ReadValue("returnValue.Member1", returnValue.Member1);
reader_eowkwedtet->ReadValue("returnValue.Member2", returnValue.Member2);
}
    
}
static void Write_SampleService_ReceiveEnum_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveEnum_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveEnum_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const naranja::generated::Sample::SampleEnum& returnValue)
{
    
    
objectWriter->WriteEnum("returnValue", returnValue);
    
}

static void Read_SampleService_ReceiveEnum_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, naranja::generated::Sample::SampleEnum& returnValue)
{
    
    
returnValue = objectReader->ReadEnum<std::remove_reference<decltype(returnValue)>::type>("returnValue");
    
}
static void Write_SampleService_ReceiveInteger_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveInteger_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveInteger_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::int64_t& returnValue)
{
    
    
objectWriter->WriteValue("returnValue", returnValue);
    
}

static void Read_SampleService_ReceiveInteger_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::int64_t& returnValue)
{
    
    
objectReader->ReadValue("returnValue", returnValue);
    
}
static void Write_SampleService_ReceiveString_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveString_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveString_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::string& returnValue)
{
    
    
objectWriter->WriteValue("returnValue", returnValue);
    
}

static void Read_SampleService_ReceiveString_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::string& returnValue)
{
    
    
objectReader->ReadValue("returnValue", returnValue);
    
}
static void Write_SampleService_ReceiveBinary_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveBinary_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveBinary_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::vector<char>& returnValue)
{
    
    
objectWriter->WriteValue("returnValue", returnValue);
    
}

static void Read_SampleService_ReceiveBinary_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::vector<char>& returnValue)
{
    
    
objectReader->ReadValue("returnValue", returnValue);
    
}
static void Write_SampleService_ReceiveListOfIntegers_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveListOfIntegers_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveListOfIntegers_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::vector<std::int64_t>& returnValue)
{
    
    
{
    auto writer_vpcfogrvhm = objectWriter->WriteList("returnValue", returnValue.size());
    for (std::size_t i = 0; i < returnValue.size(); ++i)
    {
        
writer_vpcfogrvhm->WriteValue("returnValue[i]", returnValue[i]);    
    }
}
    
}

static void Read_SampleService_ReceiveListOfIntegers_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::vector<std::int64_t>& returnValue)
{
    
    
{
    std::size_t size_nwdqgigjno;
    auto reader_qfqiqgaqda = objectReader->ReadList("returnValue", size_nwdqgigjno);
    returnValue.resize(size_nwdqgigjno);
    for (std::size_t i = 0; i < size_nwdqgigjno; ++i)
    {
        
reader_qfqiqgaqda->ReadValue("returnValue[i]", returnValue[i]);    
    }

}
    
}
static void Write_SampleService_ReceiveListOfStructs_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_ReceiveListOfStructs_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_ReceiveListOfStructs_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const std::vector<naranja::generated::Sample::SampleStruct>& returnValue)
{
    
    
{
    auto writer_vmccdyggul = objectWriter->WriteList("returnValue", returnValue.size());
    for (std::size_t i = 0; i < returnValue.size(); ++i)
    {
        
{
    auto writer_aenazlsndv = writer_vmccdyggul->WriteObject("returnValue[i]");
writer_aenazlsndv->WriteValue("returnValue[i].Member1", returnValue[i].Member1);
writer_aenazlsndv->WriteValue("returnValue[i].Member2", returnValue[i].Member2);
}    
    }
}
    
}

static void Read_SampleService_ReceiveListOfStructs_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, std::vector<naranja::generated::Sample::SampleStruct>& returnValue)
{
    
    
{
    std::size_t size_eednmxncmq;
    auto reader_uoodpccxqt = objectReader->ReadList("returnValue", size_eednmxncmq);
    returnValue.resize(size_eednmxncmq);
    for (std::size_t i = 0; i < size_eednmxncmq; ++i)
    {
        
{
    auto reader_pxosowwkjk = reader_uoodpccxqt->ReadObject("returnValue[i]");
reader_pxosowwkjk->ReadValue("returnValue[i].Member1", returnValue[i].Member1);
reader_pxosowwkjk->ReadValue("returnValue[i].Member2", returnValue[i].Member2);
}    
    }

}
    
}
static void Write_SampleService_CallFailingFunction_Request(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    (void)objectWriter;
}

static void Read_SampleService_CallFailingFunction_Request(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
    (void)objectReader;
}

static void Write_SampleService_CallFailingFunction_Response(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter)
{
    
    (void)objectWriter;
    
}

static void Read_SampleService_CallFailingFunction_Response(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader)
{
     
    (void)objectReader;
    
}



static void Write_SampleException(const std::shared_ptr<naranja::protocol::IObjectWriter>& objectWriter, const naranja::generated::Sample::SampleException& ex)
{
    
    
objectWriter->WriteValue("ex.Description", ex.Description);
    
}

static void Read_SampleException(const std::shared_ptr<naranja::protocol::IObjectReader>& objectReader, naranja::generated::Sample::SampleException& ex)
{
    
    
objectReader->ReadValue("ex.Description", ex.Description);
    
}

// -------------------------------------------------------------------------------------- Client Side Code

naranja::generated::Sample::ClientSideSampleService::ClientSideSampleService(const std::shared_ptr<naranja::rpc::ClientSideConnection>& connection, const std::shared_ptr<naranja::protocol::IProtocol>& protocol)
    : _connection(connection)
    , _protocol(protocol)
{
}


void naranja::generated::Sample::ClientSideSampleService::TransmitStruct(const naranja::generated::Sample::SampleStruct& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            Read_SampleService_TransmitStruct_Response(objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitStruct", token);
    Write_SampleService_TransmitStruct_Request(objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitEnum(const naranja::generated::Sample::SampleEnum& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            Read_SampleService_TransmitEnum_Response(objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitEnum", token);
    Write_SampleService_TransmitEnum_Request(objectWriter_,  arg);

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
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            Read_SampleService_TransmitInteger_Response(objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitInteger", token);
    Write_SampleService_TransmitInteger_Request(objectWriter_,  arg);

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
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            Read_SampleService_TransmitString_Response(objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitString", token);
    Write_SampleService_TransmitString_Request(objectWriter_,  arg);

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
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            Read_SampleService_TransmitBinary_Response(objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitBinary", token);
    Write_SampleService_TransmitBinary_Request(objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitListOfIntegers(const std::vector<std::int64_t>& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            Read_SampleService_TransmitListOfIntegers_Response(objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitListOfIntegers", token);
    Write_SampleService_TransmitListOfIntegers_Request(objectWriter_,  arg);

    return future.get();
}

void naranja::generated::Sample::ClientSideSampleService::TransmitListOfStructs(const std::vector<naranja::generated::Sample::SampleStruct>& arg)
{
    const auto token = _protocol->CreateToken();

    std::promise<void> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            Read_SampleService_TransmitListOfStructs_Response(objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.TransmitListOfStructs", token);
    Write_SampleService_TransmitListOfStructs_Request(objectWriter_,  arg);

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
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            SampleStruct result;
            Read_SampleService_ReceiveStruct_Response(objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveStruct", token);
    Write_SampleService_ReceiveStruct_Request(objectWriter_);

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
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            SampleEnum result;
            Read_SampleService_ReceiveEnum_Response(objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveEnum", token);
    Write_SampleService_ReceiveEnum_Request(objectWriter_);

    return future.get();
}

std::int64_t naranja::generated::Sample::ClientSideSampleService::ReceiveInteger()
{
    const auto token = _protocol->CreateToken();

    std::promise<std::int64_t> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            std::int64_t result;
            Read_SampleService_ReceiveInteger_Response(objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveInteger", token);
    Write_SampleService_ReceiveInteger_Request(objectWriter_);

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
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            std::string result;
            Read_SampleService_ReceiveString_Response(objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveString", token);
    Write_SampleService_ReceiveString_Request(objectWriter_);

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
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            std::vector<char> result;
            Read_SampleService_ReceiveBinary_Response(objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveBinary", token);
    Write_SampleService_ReceiveBinary_Request(objectWriter_);

    return future.get();
}

std::vector<std::int64_t> naranja::generated::Sample::ClientSideSampleService::ReceiveListOfIntegers()
{
    const auto token = _protocol->CreateToken();

    std::promise<std::vector<std::int64_t>> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            std::vector<std::int64_t> result;
            Read_SampleService_ReceiveListOfIntegers_Response(objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveListOfIntegers", token);
    Write_SampleService_ReceiveListOfIntegers_Request(objectWriter_);

    return future.get();
}

std::vector<naranja::generated::Sample::SampleStruct> naranja::generated::Sample::ClientSideSampleService::ReceiveListOfStructs()
{
    const auto token = _protocol->CreateToken();

    std::promise<std::vector<SampleStruct>> promise;
    auto future = promise.get_future();

    auto disposer = _connection->RegisterFunctionResponseHandler(token, [this, &promise](const std::shared_ptr<protocol::IObjectReader>& objectReader) mutable {
        try
        {
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            
            std::vector<SampleStruct> result;
            Read_SampleService_ReceiveListOfStructs_Response(objectReader, result);
            promise.set_value(result);
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.ReceiveListOfStructs", token);
    Write_SampleService_ReceiveListOfStructs_Request(objectWriter_);

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
            if (objectReader->Identifier() == "ProtocolBaseException")
            {
                std::string message("");
                objectReader->ReadValue("message", message);
                throw naranja::core::ProtocolBaseException(message);
            }
            
            if (objectReader->Identifier() == "Sample.SampleException")
            {
                generated::Sample::SampleException ex;
                Read_SampleException(objectReader, ex);
                throw ex;
            }
            
            
            Read_SampleService_CallFailingFunction_Response(objectReader);
            promise.set_value();
            
        }
        catch(...)
        {
            promise.set_exception(std::current_exception());
        }
    });

    auto outputStream_ = _connection->ReserveOutputStream();
    auto objectWriter_ = _protocol->WriteObject(*outputStream_, naranja::protocol::ObjectType::FunctionCall, "SampleService.CallFailingFunction", token);
    Write_SampleService_CallFailingFunction_Request(objectWriter_);

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


void naranja::generated::Sample::ServerSideSampleService::TransmitStruct(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    SampleStruct arg;
    Read_SampleService_TransmitStruct_Request(object_,  arg);
    try
    {
        _service->TransmitStruct( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitStruct", object_->Token());
        Write_SampleService_TransmitStruct_Response(responseObject_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitEnum(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    SampleEnum arg;
    Read_SampleService_TransmitEnum_Request(object_,  arg);
    try
    {
        _service->TransmitEnum( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitEnum", object_->Token());
        Write_SampleService_TransmitEnum_Response(responseObject_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitInteger(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::int64_t arg;
    Read_SampleService_TransmitInteger_Request(object_,  arg);
    try
    {
        _service->TransmitInteger( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitInteger", object_->Token());
        Write_SampleService_TransmitInteger_Response(responseObject_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitString(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::string arg;
    Read_SampleService_TransmitString_Request(object_,  arg);
    try
    {
        _service->TransmitString( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitString", object_->Token());
        Write_SampleService_TransmitString_Response(responseObject_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitBinary(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::vector<char> arg;
    Read_SampleService_TransmitBinary_Request(object_,  arg);
    try
    {
        _service->TransmitBinary( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitBinary", object_->Token());
        Write_SampleService_TransmitBinary_Response(responseObject_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitListOfIntegers(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::vector<std::int64_t> arg;
    Read_SampleService_TransmitListOfIntegers_Request(object_,  arg);
    try
    {
        _service->TransmitListOfIntegers( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitListOfIntegers", object_->Token());
        Write_SampleService_TransmitListOfIntegers_Response(responseObject_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::TransmitListOfStructs(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    
    std::vector<SampleStruct> arg;
    Read_SampleService_TransmitListOfStructs_Request(object_,  arg);
    try
    {
        _service->TransmitListOfStructs( arg);
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.TransmitListOfStructs", object_->Token());
        Write_SampleService_TransmitListOfStructs_Response(responseObject_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveStruct(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveStruct_Request(object_);
    try
    {
        auto result_ =_service->ReceiveStruct();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveStruct", object_->Token());
        Write_SampleService_ReceiveStruct_Response(responseObject_, result_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveEnum(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveEnum_Request(object_);
    try
    {
        auto result_ =_service->ReceiveEnum();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveEnum", object_->Token());
        Write_SampleService_ReceiveEnum_Response(responseObject_, result_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveInteger(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveInteger_Request(object_);
    try
    {
        auto result_ =_service->ReceiveInteger();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveInteger", object_->Token());
        Write_SampleService_ReceiveInteger_Response(responseObject_, result_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveString(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveString_Request(object_);
    try
    {
        auto result_ =_service->ReceiveString();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveString", object_->Token());
        Write_SampleService_ReceiveString_Response(responseObject_, result_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveBinary(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveBinary_Request(object_);
    try
    {
        auto result_ =_service->ReceiveBinary();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveBinary", object_->Token());
        Write_SampleService_ReceiveBinary_Response(responseObject_, result_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveListOfIntegers(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveListOfIntegers_Request(object_);
    try
    {
        auto result_ =_service->ReceiveListOfIntegers();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveListOfIntegers", object_->Token());
        Write_SampleService_ReceiveListOfIntegers_Response(responseObject_, result_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::ReceiveListOfStructs(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_ReceiveListOfStructs_Request(object_);
    try
    {
        auto result_ =_service->ReceiveListOfStructs();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.ReceiveListOfStructs", object_->Token());
        Write_SampleService_ReceiveListOfStructs_Response(responseObject_, result_);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
void naranja::generated::Sample::ServerSideSampleService::CallFailingFunction(const std::shared_ptr<protocol::IObjectReader>& object_, const std::shared_ptr<naranja::rpc::ServerSideConnection>& connection_)
{
    // TODO: use threadpool

    Read_SampleService_CallFailingFunction_Request(object_);
    try
    {
        _service->CallFailingFunction();
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::FunctionResponse, "SampleService.CallFailingFunction", object_->Token());
        Write_SampleService_CallFailingFunction_Response(responseObject_);
    }
    catch (const naranja::generated::Sample::SampleException& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "Sample.SampleException", object_->Token());
        Write_SampleException(responseObject_, ex);
    }
    catch (const std::exception& ex)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string(ex.what()));
    }
    catch (...)
    {
        auto reservedOutputStream_ = connection_->ReserveOutputStream();
        auto responseObject_ = _protocol->WriteObject(*reservedOutputStream_, naranja::protocol::ObjectType::Exception, "ProtocolBaseException", object_->Token());
        responseObject_->WriteValue("message", std::string("Unkonwn exception type caught."));
    }
}
