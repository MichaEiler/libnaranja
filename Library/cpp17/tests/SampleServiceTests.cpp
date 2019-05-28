#include "common/SampleService.hpp"

#include <naranja/protocol/one/Protocol.hpp>
#include <naranja/rpc/Server.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <gmock/gmock.h>

constexpr std::uint16_t NetworkPortForTests = 50674u;

class SampleServiceTestFixture : public testing::Test
{
};

class SampleServiceImpl : public naranja::generated::Sample::ISampleService
{
public:
    void FunctionThrowingSampleException() override
    {
        naranja::generated::Sample::SampleException ex;
        ex.Description = "SampleException with a description";
        throw ex;
    }

    naranja::generated::Sample::SampleStruct FunctionReturningData(const naranja::generated::Sample::SampleEnum& arg1) override
    {
        naranja::generated::Sample::SampleStruct result;
        result.Member1 = arg1 == naranja::generated::Sample::SampleEnum::Entry0 ? 42 : 1337;
        result.Member2 = "What's the question?";
        return result;
    }
};

TEST_F(SampleServiceTestFixture, FunctionCall_ServiceProcessesCall_ReturnsResult)
{
    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();

    auto server = naranja::rpc::Server::Create(protocol, NetworkPortForTests);
    server->RegisterService(naranja::generated::Sample::ServerSideSampleService::Create(std::make_shared<SampleServiceImpl>(), protocol));
    server->Start();

    auto client = naranja::rpc::ClientSideConnection::Create(protocol);
    auto sampleService = naranja::generated::Sample::ClientSideSampleService::Create(client, protocol);
    client->Start("127.0.0.1", NetworkPortForTests);


    const auto result = sampleService->FunctionReturningData(naranja::generated::Sample::SampleEnum::Entry0);
    ASSERT_EQ(42, result.Member1);

    const auto result2 = sampleService->FunctionReturningData(naranja::generated::Sample::SampleEnum::Entry1);
    ASSERT_EQ(1337, result2.Member1);
}

TEST_F(SampleServiceTestFixture, FunctionCall_ThrowsException_ExceptionTransmitted)
{
    auto proto = std::make_shared<naranja::protocol::one::Protocol>();

    auto server = naranja::rpc::Server::Create(proto, NetworkPortForTests);
    server->RegisterService(naranja::generated::Sample::ServerSideSampleService::Create(std::make_shared<SampleServiceImpl>(), proto));
    server->Start();

    auto client = naranja::rpc::ClientSideConnection::Create(proto);
    auto sampleService = naranja::generated::Sample::ClientSideSampleService::Create(client, proto);
    client->Start("127.0.0.1", NetworkPortForTests);

    ASSERT_THROW(sampleService->FunctionThrowingSampleException(), naranja::generated::Sample::SampleException);
}