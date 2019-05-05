#include "common/SampleService.hpp"

#include <naranja/protocol/one/Protocol.hpp>
#include <naranja/rpc/Server.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <iostream>
#include <gmock/gmock.h>

constexpr std::uint16_t NetworkPortForTests = 50674u;

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

    naranja::generated::SampleStruct FunctionReturningData(const naranja::generated::SampleEnum& arg1) override
    {
        naranja::generated::SampleStruct result;
        result.Member1 = arg1 == naranja::generated::SampleEnum::Entry0 ? 42 : 1337;
        result.Member2 = "What's the question?";
        return result;
    }

    naranja::utils::Disposer OnSampleEvent(const std::function<void(const std::string& value)>& eventHandler) override
    {
        // TODO: Implement later on
        return naranja::utils::Disposer([](){});
    }
};

TEST_F(SampleServiceTestFixture, FunctionCall_ServiceProcessesCall_ReturnsResult)
{
    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();

    auto server = naranja::rpc::Server::Create(protocol, NetworkPortForTests);
    server->RegisterService(naranja::generated::ServerSideSampleService::Create(std::make_shared<SampleServiceImpl>(), protocol));
    server->Start();


    auto client = naranja::rpc::ClientSideConnection::Create(protocol);
    auto sampleService = naranja::generated::ClientSideSampleService::Create(client, protocol);
    client->Start("127.0.0.1", NetworkPortForTests);


    const auto result = sampleService->FunctionReturningData(naranja::generated::SampleEnum::Entry0);
    ASSERT_EQ(42, result.Member1);

    const auto result2 = sampleService->FunctionReturningData(naranja::generated::SampleEnum::Entry1);
    ASSERT_EQ(1337, result2.Member1);
}

TEST_F(SampleServiceTestFixture, Test1)
{
    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();

    auto server = naranja::rpc::Server::Create(protocol, NetworkPortForTests);
    server->RegisterService(naranja::generated::ServerSideSampleService::Create(std::make_shared<SampleServiceImpl>(), protocol));
    server->Start();


    auto client = naranja::rpc::ClientSideConnection::Create(protocol);
    auto sampleService = naranja::generated::ClientSideSampleService::Create(client, protocol);
    client->Start("127.0.0.1", NetworkPortForTests);

    const std::uint16_t port = 16666;

    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();

    auto server = naranja::rpc::Server::Create(protocol, port);
    server->RegisterService(naranja::generated::ServerSideSampleService::Create(std::make_shared<SampleServiceImpl>(), protocol));
    server->Start();


    auto client = naranja::rpc::ClientSideConnection::Create(protocol);
    auto sampleService = naranja::generated::ClientSideSampleService::Create(client, protocol);
    client->Start("127.0.0.1", port);


    const auto result = sampleService->FunctionReturningData(naranja::generated::SampleEnum::Entry0);
    ASSERT_EQ(42, result.Member1);

    const auto result2 = sampleService->FunctionReturningData(naranja::generated::SampleEnum::Entry1);
    ASSERT_EQ(1337, result2.Member1);

    ASSERT_THROW(sampleService->FunctionThrowingSampleException(), naranja::generated::SampleException);
}