#include "common/Sample.hpp"

#include <naranja/protocol/one/Protocol.hpp>
#include <naranja/rpc/Server.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <gmock/gmock.h>

constexpr std::uint16_t NetworkPortForTests = 50674u;

struct SampleServiceImpl : public naranja::generated::Sample::ISampleService
{
    naranja::generated::Sample::SampleStruct _argStruct;
    naranja::generated::Sample::SampleEnum _argEnum;
    std::int64_t _argInt;
    std::string _argStr;
    std::vector<char> _argBinary;
    std::vector<std::int64_t> _argIntList;
    std::vector<naranja::generated::Sample::SampleStruct >_argStructList;

    void TransmitStruct(const naranja::generated::Sample::SampleStruct& arg) override { _argStruct = arg; }
    void TransmitEnum(const naranja::generated::Sample::SampleEnum& arg) override { _argEnum = arg; }
    void TransmitInteger(const std::int64_t& arg) override { _argInt = arg; }
    void TransmitString(const std::string& arg) override { _argStr = arg; }
    void TransmitBinary(const std::vector<char>& arg) override { _argBinary = arg; }
    void TransmitListOfIntegers(const std::vector<std::int64_t>& arg) override { _argIntList = arg; }
    void TransmitListOfStructs(const std::vector<naranja::generated::Sample::SampleStruct>& arg) override { _argStructList = arg; }
    naranja::generated::Sample::SampleStruct ReceiveStruct() override { return _argStruct; }
    naranja::generated::Sample::SampleEnum ReceiveEnum() override { return _argEnum; }
    std::int64_t ReceiveInteger() override { return _argInt; }
    std::string ReceiveString() override { return _argStr; }
    std::vector<char> ReceiveBinary() override { return _argBinary; }
    std::vector<std::int64_t> ReceiveListOfIntegers() override { return _argIntList; }
    std::vector<naranja::generated::Sample::SampleStruct> ReceiveListOfStructs() override { return _argStructList; }
    void CallFailingFunction() override { naranja::generated::Sample::SampleException ex; ex.Description = "Ex"; throw ex; }
};

class SampleServiceTestFixture : public testing::Test
{
protected:
    std::shared_ptr<SampleServiceImpl> _serviceImpl;

    std::shared_ptr<naranja::protocol::IProtocol> _protocol;
    std::shared_ptr<naranja::rpc::Server> _server;

    std::shared_ptr<naranja::rpc::ClientSideConnection> _client;
    std::shared_ptr<naranja::generated::Sample::ClientSideSampleService> _service;

public:
    void SetUp() override
    {
        _serviceImpl = std::make_shared<SampleServiceImpl>();
        _protocol = std::make_shared<naranja::protocol::one::Protocol>();;

        _server = naranja::rpc::Server::Create(_protocol, NetworkPortForTests);
        _server->RegisterService(naranja::generated::Sample::ServerSideSampleService::Create(_serviceImpl, _protocol));
        _server->Start();

        _client = naranja::rpc::ClientSideConnection::Create(_protocol);
        _service = naranja::generated::Sample::ClientSideSampleService::Create(_client, _protocol);
        _client->Start("127.0.0.1", NetworkPortForTests);
    }

    void TearDown() override
    {
        _service.reset();
        _client.reset();
        _server.reset();
        _protocol.reset();
        _serviceImpl.reset();
    }

};

TEST_F(SampleServiceTestFixture, FunctionCall_TransmitStruct_ResultValid)
{
    const naranja::generated::Sample::SampleStruct value{ 123, "HelloWorld" };

    _service->TransmitStruct(value);
    
    ASSERT_EQ(value.Member1, _serviceImpl->_argStruct.Member1);
    ASSERT_EQ(value.Member2, _serviceImpl->_argStruct.Member2);
}

TEST_F(SampleServiceTestFixture, FunctionCall_TransmitEnum_ResultValid)
{
    const auto value = naranja::generated::Sample::SampleEnum::Entry1;

    _service->TransmitEnum(value);

    ASSERT_EQ(value, _serviceImpl->_argEnum);
}

TEST_F(SampleServiceTestFixture, FunctionCall_TransmitInteger_ResultValid)
{
    const auto value = std::int64_t(17);

    _service->TransmitInteger(value);

    ASSERT_EQ(value, _serviceImpl->_argInt);
}

TEST_F(SampleServiceTestFixture, FunctionCall_TransmitString_ResultValid)
{
    const std::string value("HelloWorld");

    _service->TransmitString(value);

    ASSERT_EQ(value, _serviceImpl->_argStr);
}

TEST_F(SampleServiceTestFixture, FunctionCall_TransmitBinary_ResultValid)
{
    const std::vector<char> value({'\x20', '\x30', '\x40', '\x50', '\x60'});

    _service->TransmitBinary(value);

    ASSERT_EQ(value, _serviceImpl->_argBinary);
}

TEST_F(SampleServiceTestFixture, FunctionCall_TransmitListOfIntegers_ResultValid)
{
    const std::vector<std::int64_t> value({ 123ll, 456ll, 789ll});

    _service->TransmitListOfIntegers(value);

    ASSERT_EQ(value, _serviceImpl->_argIntList);
}

TEST_F(SampleServiceTestFixture, FunctionCall_TransmitListOfStructs_ResultValid)
{
    const std::vector<naranja::generated::Sample::SampleStruct> values({ { 123ll, "HelloWorld" }, { 456ll, "WeReGoingToIbiza" } });

    _service->TransmitListOfStructs(values);

    ASSERT_EQ(2, _serviceImpl->_argStructList.size());
    ASSERT_EQ(values[0].Member1, _serviceImpl->_argStructList[0].Member1);
    ASSERT_EQ(values[0].Member2, _serviceImpl->_argStructList[0].Member2);
    ASSERT_EQ(values[1].Member1, _serviceImpl->_argStructList[1].Member1);
    ASSERT_EQ(values[1].Member2, _serviceImpl->_argStructList[1].Member2);
}

TEST_F(SampleServiceTestFixture, FunctionCall_ReceiveStruct_ResultValid)
{
    const naranja::generated::Sample::SampleStruct expectedResult{ 123, "HelloWorld" };
    _serviceImpl->_argStruct = expectedResult;

    auto result = _service->ReceiveStruct();

    ASSERT_EQ(expectedResult.Member1, result.Member1);
    ASSERT_EQ(expectedResult.Member2, result.Member2);
}

TEST_F(SampleServiceTestFixture, FunctionCall_ReceiveEnum_ResultValid)
{
    const auto expectedResult = naranja::generated::Sample::SampleEnum::Entry1;
    _serviceImpl->_argEnum = expectedResult;

    auto result = _service->ReceiveEnum();

    ASSERT_EQ(expectedResult, result);
}

TEST_F(SampleServiceTestFixture, FunctionCall_ReceiveInteger_ResultValid)
{
    const auto expectedResult = 1234567890ll;
    _serviceImpl->_argInt = expectedResult;

    auto result = _service->ReceiveInteger();

    ASSERT_EQ(expectedResult, result);
}

TEST_F(SampleServiceTestFixture, FunctionCall_ReceiveString_ResultValid)
{
    const std::string expectedResult("HelloWorld");
    _serviceImpl->_argStr = expectedResult;

    auto result = _service->ReceiveString();

    ASSERT_EQ(expectedResult, result);
}

TEST_F(SampleServiceTestFixture, FunctionCall_ReceiveBinary_ResultValid)
{
    const std::vector<char> expectedResult({'\x20', '\x30', '\x40', '\x50', '\x60'});
    _serviceImpl->_argBinary = expectedResult;

    auto result = _service->ReceiveBinary();

    ASSERT_EQ(expectedResult, result);
}

TEST_F(SampleServiceTestFixture, FunctionCall_ReceiveListOfIntegers_ResultValid)
{
    const std::vector<std::int64_t> expectedResult({ 123ll, 456ll, 789ll });
    _serviceImpl->_argIntList = expectedResult;

    auto result = _service->ReceiveListOfIntegers();

    ASSERT_EQ(expectedResult, result);
}

TEST_F(SampleServiceTestFixture, FunctionCall_ReceiveListOfStructs_ResultValid)
{
    const std::vector<naranja::generated::Sample::SampleStruct> expectedResult({ { 123ll, "HelloWorld" }, { 456ll, "WeReGoingToIbiza" } });
    _serviceImpl->_argStructList = expectedResult;

    auto result = _service->ReceiveListOfStructs();

    ASSERT_EQ(2, _serviceImpl->_argStructList.size());
    ASSERT_EQ(expectedResult[0].Member1, _serviceImpl->_argStructList[0].Member1);
    ASSERT_EQ(expectedResult[0].Member2, _serviceImpl->_argStructList[0].Member2);
    ASSERT_EQ(expectedResult[1].Member1, _serviceImpl->_argStructList[1].Member1);
    ASSERT_EQ(expectedResult[1].Member2, _serviceImpl->_argStructList[1].Member2);
}

TEST_F(SampleServiceTestFixture, FunctionCall_CallFailingFunction_CorrectExceptionTransmitted)
{
    ASSERT_THROW(_service->CallFailingFunction(), naranja::generated::Sample::SampleException);
}

TEST_F(SampleServiceTestFixture, NoAction_ImmediateTearDown_NoExceptionThrown)
{
    ASSERT_NO_THROW(TearDown());
}