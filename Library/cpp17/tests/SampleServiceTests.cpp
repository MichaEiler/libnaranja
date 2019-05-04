#include "common/SampleService.hpp"

#include <naranja/protocol/one/Protocol.hpp>
#include <naranja/rpc/Server.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <iostream>
#include <gmock/gmock.h>

class SampleServiceTestFixture : public testing::Test
{
};

class SampleServiceImpl : public naranja::generated::ISampleService
{
public:
    void FunctionThrowingSampleException() override
    {
        naranja::generated::SampleException ex;
        ex.Description = "SampleException with a description";
        throw ex;
    }

    void FunctionReturningData(naranja::generated::SampleStruct& result, const naranja::generated::SampleEnum& arg1) override
    {
        result.Member1 = arg1 == naranja::generated::SampleEnum::Entry0 ? 42 : 1337;
        result.Member2 = "What's the question?";
    }

    naranja::utils::Disposer OnSampleEvent(const std::function<void(const std::string& value)>& eventHandler) override
    {
        // TODO: Implement later on
        return naranja::utils::Disposer([](){});
    }
};

TEST_F(SampleServiceTestFixture, Test1)
{
    const std::uint16_t port = 16666;

    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();

    auto server = naranja::rpc::Server::Create(protocol, port);
    server->RegisterService(naranja::generated::ServerSideSampleService::Create(std::make_shared<SampleServiceImpl>(), protocol));
    server->Start();


    auto client = naranja::rpc::ClientSideConnection::Create(protocol);
    auto sampleService = naranja::generated::ClientSideSampleService::Create(client, protocol);
    client->Start("127.0.0.1", port);

    naranja::generated::SampleStruct result;
    sampleService->FunctionReturningData(result, naranja::generated::SampleEnum::Entry0);
    std::cout << "Received result: " << result.Member1 << std::endl;
    std::cout << "Received result: " << result.Member2 << std::endl;

    sampleService->FunctionReturningData(result, naranja::generated::SampleEnum::Entry1);
    std::cout << "Received result: " << result.Member1 << std::endl;
    std::cout << "Received result: " << result.Member2 << std::endl;

    try
    {
   
    
    sampleService->FunctionThrowingSampleException();
     }
    catch(const naranja::generated::SampleException& ex)
    {
        std::cerr << ex.Description << "\n";
    }
}