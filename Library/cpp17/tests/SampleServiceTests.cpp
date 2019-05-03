#include "common/SampleService.hpp"

#include <naranja/protocol/ObjectBrokerFactory.hpp>
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
        ex.Description = "Just a sample...";
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
    auto serverService = std::make_shared<SampleServiceImpl>();
    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();
    auto objectBrokerFactory = std::make_shared<naranja::protocol::ObjectBrokerFactory>(protocol);

    const std::uint16_t port = 16666;
    auto server = std::make_shared<naranja::rpc::Server>(objectBrokerFactory, port);

    server->RegisterService(naranja::generated::ServerSideSampleService::Create(serverService, protocol));
    server->Start();




    auto clientObjectBroker = std::dynamic_pointer_cast<naranja::protocol::ObjectBroker>(objectBrokerFactory->Create());
    auto client = std::make_shared<naranja::rpc::ClientSideConnection>(clientObjectBroker);
    auto clientService = naranja::generated::ClientSideSampleService::Create(clientObjectBroker, client, protocol);

    client->Connect("127.0.0.1", port);

    naranja::generated::SampleStruct result;
    clientService->FunctionReturningData(result, naranja::generated::SampleEnum::Entry0);
    std::cout << "Received result: " << result.Member1 << std::endl;
    std::cout << "Received result: " << result.Member2 << std::endl;

    clientService->FunctionReturningData(result, naranja::generated::SampleEnum::Entry1);
    std::cout << "Received result: " << result.Member1 << std::endl;
    std::cout << "Received result: " << result.Member2 << std::endl;

    client->Close();
    server->Stop();

}