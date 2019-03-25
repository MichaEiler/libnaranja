#include <cstdint>
#include <gmock/gmock.h>
#include <memory>
#include <Rpc2/Protocol/One/Protocol.hpp>
#include <Rpc2/Streams/StdInputStream.hpp>
#include <sstream>
#include <variant>

class ProtocolOneTestFixture : public testing::Test
{
};

TEST_F(ProtocolOneTestFixture, PeekNextObjectType_FunctionCallInStream_CorrectTypeReturned)
{
    std::string encodedData("\x01\x00\x00\x00", 4);
    auto memoryStream = std::make_shared<std::stringstream>(encodedData);
    auto inputStream = std::make_shared<Rpc2::Streams::StdInputStream>(memoryStream);
    auto bufferedInputStream = std::make_shared<Rpc2::Streams::BufferedInputStream>(inputStream, encodedData.size());

    const auto protocol = std::make_shared<Rpc2::Protocol::One::Protocol>();
    const auto actualProtocol = protocol->PeekNextObjectType(bufferedInputStream);
    const auto expectedProtocol = Rpc2::Protocol::ObjectType::FunctionCall;
    
    ASSERT_EQ(actualProtocol, expectedProtocol);
}

TEST_F(ProtocolOneTestFixture, PeekNextToken_EventInStream_ThrowsRuntimeError)
{
    std::string encodedData("\x04\x00\x00\x00", 4);
    auto memoryStream = std::make_shared<std::stringstream>(encodedData);
    auto inputStream = std::make_shared<Rpc2::Streams::StdInputStream>(memoryStream);
    auto bufferedInputStream = std::make_shared<Rpc2::Streams::BufferedInputStream>(inputStream, encodedData.size());

    auto protocol = std::make_shared<Rpc2::Protocol::One::Protocol>();
    ASSERT_THROW(protocol->PeekNextToken(bufferedInputStream), std::runtime_error);
}

TEST_F(ProtocolOneTestFixture, PeekNextToken_ObjectInStream_ReturnsToken)
{
    std::string encodedData("\x01\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00HelloToken", 22);
    auto memoryStream = std::make_shared<std::stringstream>(encodedData);
    auto inputStream = std::make_shared<Rpc2::Streams::StdInputStream>(memoryStream);
    auto bufferedInputStream = std::make_shared<Rpc2::Streams::BufferedInputStream>(inputStream, encodedData.size());

    auto protocol = std::make_shared<Rpc2::Protocol::One::Protocol>();
    auto token = protocol->PeekNextToken(bufferedInputStream);

    const std::string expectedToken("HelloToken");
    ASSERT_STREQ(token.c_str(), expectedToken.c_str());
}

/*TEST_F(ProtocolOneTestFixture, stdVariant)
{
    std::variant<std::uint64_t*, std::uint32_t*, std::uint16_t*, std::uint8_t*> var;
    std::uint8_t val = 1;
    var = &val;


}*/

