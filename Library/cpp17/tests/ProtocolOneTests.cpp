#include <cstdint>
#include <cstring>
#include <gmock/gmock.h>
#include <memory>
#include <naranja/protocol/one/ObjectReader.hpp>
#include <naranja/protocol/one/ObjectWriter.hpp>
#include <naranja/protocol/one/Protocol.hpp>
#include <naranja/streams/MemoryStream.hpp>
#include <sstream>
#include <type_traits>
#include <vector>

#include <common/BufferedStreams.hpp>

constexpr static std::size_t SmallCacheSize = 1024;

class ProtocolOneTestFixture : public testing::Test
{
public:
    template <typename TValue>
    void TestPrimitiveSerialization(const TValue& value, const std::string& encodedValue) const
    {
        naranja::streams::MemoryStream memoryStream(SmallCacheSize);
        
        {
            naranja::tests::BufferedOutputStream bufferedOutputStream(memoryStream);
            naranja::protocol::one::Protocol protocol;
            naranja::protocol::one::ObjectWriter objectWriter(bufferedOutputStream);
            objectWriter.WriteValue("", value);
        }

        std::string result;
        result.resize(1024, '\0');

        auto receivedBytes = memoryStream.TryRead(&result[0], result.size());
        result.resize(receivedBytes);
        ASSERT_EQ(receivedBytes, encodedValue.size());
        ASSERT_TRUE(result == encodedValue);
    };

    template <typename TValue>
    void TestPrimitiveParsing(const std::string& encodedValue, const TValue& expectedValue) const
    {
        naranja::streams::MemoryStream memoryStream(SmallCacheSize);
        memoryStream.Write(encodedValue.data(), encodedValue.size());

        naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);
        naranja::protocol::one::ObjectReader objectReader(bufferedInputStream);

        TValue result;
        objectReader.ReadValue("", result);

        ASSERT_TRUE(result == expectedValue);
    }
};


TEST_F(ProtocolOneTestFixture, GenerateToken_SizeOfTokenValid)
{
    const auto protocol = std::make_shared<naranja::protocol::one::Protocol>();
    const auto token = protocol->CreateToken();

    const std::size_t expectedTokenSize = 8;
    ASSERT_EQ(token.size(), expectedTokenSize);
}

TEST_F(ProtocolOneTestFixture, PeekNextObjectType_FunctionCallInStream_CorrectTypeReturned)
{
    naranja::streams::MemoryStream memoryStream;
    naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);

    const std::string encodedData("\x01\x00\x00\x00", 4);
    memoryStream.Write(encodedData.data(), encodedData.size());

    const auto protocol = std::make_shared<naranja::protocol::one::Protocol>();
    const auto actualProtocol = protocol->PeekNextObjectType(bufferedInputStream);
    const auto expectedProtocol = naranja::protocol::ObjectType::FunctionCall;
    
    ASSERT_EQ(actualProtocol, expectedProtocol);
}

TEST_F(ProtocolOneTestFixture, PeekNextToken_EventInStream_ThrowsRuntimeError)
{
    naranja::streams::MemoryStream memoryStream;
    naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);

    std::string encodedData("\x04\x00\x00\x00", 4);
    memoryStream.Write(encodedData.data(), encodedData.size());

    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();
    ASSERT_THROW(protocol->PeekNextToken(bufferedInputStream), std::runtime_error);
}

TEST_F(ProtocolOneTestFixture, PeekNextToken_ObjectInStream_ReturnsToken)
{
    naranja::streams::MemoryStream memoryStream;
    naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);

    const std::string encodedData("\x01\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00HelloToken", 22);
    memoryStream.Write(encodedData.data(), encodedData.size());

    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();
    auto token = protocol->PeekNextToken(bufferedInputStream);

    const std::string expectedToken("HelloToken");
    ASSERT_STREQ(token.c_str(), expectedToken.c_str());
}

TEST_F(ProtocolOneTestFixture, ReadObject_FunctionCall_CorrectlyParsed)
{
    const auto expectedObjectType = naranja::protocol::ObjectType::FunctionCall;
    const std::string expectedToken("12345678");
    const std::string expectedIdentifier("Foobar_DoSomethingFunny");
    const bool expectedMember1 = true;
    const std::uint32_t expectedMember2 = 0xdeadbeefu;
    const std::string expectedMember3("SomeInformation");

    const auto createEncodedFunctionCall = [&]() -> std::string {
        std::stringstream stream;

        // header
        stream.write("\x01\x00\x00\x00", 4);                      // object type: FunctionCall

        if (8u != expectedToken.size())
            throw std::invalid_argument("Test values have been tampered with.");
        stream.write("\x08\x00\x00\x00\x00\x00\x00\x00", 8);
        stream.write(expectedToken.data(), expectedToken.size()); // actual token: 12345678

        if (23u != expectedIdentifier.size())
            throw std::invalid_argument("Test values have been tampered with.");
        stream.write("\x17\x00\x00\x00\x00\x00\x00\x00", 8);
        stream.write(expectedIdentifier.data(), expectedIdentifier.size());

        // object content
        stream.write("\x01", 1);
        stream.write("\xef\xbe\xad\xde", 4);

        if (15u != expectedMember3.size())
            throw std::invalid_argument("Test values have been tampered with.");
        stream.write("\x0f\x00\x00\x00\x00\x00\x00\x00SomeInformation", 8u + expectedMember3.size());

        return stream.str();
    };

    naranja::streams::MemoryStream memoryStream;
    naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);
    
    const auto encodedObject = createEncodedFunctionCall();
    memoryStream.Write(encodedObject.data(), encodedObject.size());
    
    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();
    auto objectReader = protocol->ReadObject(bufferedInputStream);

    ASSERT_EQ(expectedObjectType, objectReader->Type());
    ASSERT_EQ(expectedToken, objectReader->Token());
    ASSERT_EQ(expectedIdentifier, objectReader->Identifier());

    bool resultMember1 = false;
    std::uint32_t resultMember2 = 0u;
    std::vector<char> resultMember3;

    objectReader->ReadValue("", resultMember1);
    objectReader->ReadValue("", resultMember2);
    objectReader->ReadValue("", resultMember3);

    ASSERT_EQ(resultMember1, expectedMember1);
    ASSERT_EQ(resultMember2, expectedMember2);
    ASSERT_STREQ(std::string(resultMember3.data(), resultMember3.size()).c_str(), expectedMember3.c_str());
}

TEST_F(ProtocolOneTestFixture, ReadObject_Event_CorrectlyParsed)
{
    const auto expectedObjectType = naranja::protocol::ObjectType::Event;
    const std::string expectedIdentifier("Notification");
    const std::uint32_t expectedNotificationType = 0x01u;
    const std::string expectedNotificationDescription = "This is some random notification with id 1.";

    const auto createEncodedFunctionCall = [&]() -> std::string {
        std::stringstream stream;

        // header
        stream.write("\x04\x00\x00\x00", 4);                      // object type: Event

        if (12u != expectedIdentifier.size())
            throw std::invalid_argument("Test values have been tampered with.");
        stream.write("\x0c\x00\x00\x00\x00\x00\x00\x00", 8);
        stream.write(expectedIdentifier.data(), expectedIdentifier.size());

        // object content
        stream.write("\x01\x00\x00\x00", 4);

        if (43u != expectedNotificationDescription.size())
            throw std::invalid_argument("Test values have been tampered with.");
        stream.write("\x2b\x00\x00\x00\x00\x00\x00\x00", 8);
        stream.write(expectedNotificationDescription.data(), expectedNotificationDescription.size());

        return stream.str();
    };
    
    naranja::streams::MemoryStream memoryStream;
    naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);
    
    const auto encodedObject = createEncodedFunctionCall();
    memoryStream.Write(encodedObject.data(), encodedObject.size());
    
    auto protocol = std::make_shared<naranja::protocol::one::Protocol>();
    auto objectReader = protocol->ReadObject(bufferedInputStream);

    ASSERT_EQ(expectedObjectType, objectReader->Type());
    ASSERT_EQ(expectedIdentifier, objectReader->Identifier());

    std::uint32_t notificationTypeResult = 0u;
    std::string notificationDescriptionResult;

    objectReader->ReadValue("", notificationTypeResult);
    objectReader->ReadValue("", notificationDescriptionResult);

    ASSERT_EQ(notificationTypeResult, expectedNotificationType);
    ASSERT_EQ(notificationDescriptionResult, expectedNotificationDescription);
}

TEST_F(ProtocolOneTestFixture, WriteObject_FunctionCall_CorrectlySerialized)
{
    const auto objectType = naranja::protocol::ObjectType::FunctionCall;
    const std::string token("12345678");
    const std::string identifier("Identifier");

    const std::string encodedFunctionCall(
        "\x01\x00\x00\x00"
        "\x08\x00\x00\x00\x00\x00\x00\x00" "12345678"
        "\x0a\x00\x00\x00\x00\x00\x00\x00" "Identifier", 
        sizeof(std::uint32_t) + sizeof(std::uint64_t) + sizeof(std::uint64_t)
        + token.size() + identifier.size());

    naranja::streams::MemoryStream memoryStream(SmallCacheSize);
    {
        naranja::tests::BufferedOutputStream bufferedOutputStream(memoryStream);
        auto protocol = std::make_shared<naranja::protocol::one::Protocol>();

        auto object = protocol->WriteObject(bufferedOutputStream, objectType, identifier, token);
        object.reset();
    }

    std::string result;
    result.resize(SmallCacheSize);
    const auto resultSize = memoryStream.TryRead(&result[0], result.size());
    result.resize(resultSize);

    ASSERT_TRUE(result == encodedFunctionCall);
}

TEST_F(ProtocolOneTestFixture, WriteObject_Event_CorrectlySerialized)
{
    const auto objectType = naranja::protocol::ObjectType::Event;
    const std::string identifier("Identifier");

    const std::string encodedEvent(
        "\x04\x00\x00\x00"
        "\x0a\x00\x00\x00\x00\x00\x00\x00" "Identifier", 
        sizeof(std::uint32_t) + sizeof(std::uint64_t)
        + identifier.size());

    naranja::streams::MemoryStream memoryStream(SmallCacheSize);
    {
        naranja::tests::BufferedOutputStream bufferedOutputStream(memoryStream);
        auto protocol = std::make_shared<naranja::protocol::one::Protocol>();

        auto object = protocol->WriteObject(bufferedOutputStream, objectType, identifier, naranja::protocol::ObjectToken(""));
        object.reset();
    }

    std::string result;
    result.resize(SmallCacheSize);
    const auto resultSize = memoryStream.TryRead(&result[0], result.size());
    result.resize(resultSize);

    ASSERT_TRUE(result == encodedEvent);
}

TEST_F(ProtocolOneTestFixture, ReadValue_PrimitiveTypes_CorrectlyParsed)
{
    TestPrimitiveParsing(std::string("\x11", 1), std::uint8_t(0x11u));
    TestPrimitiveParsing(std::string("\x22\x11", 2), std::uint16_t(0x1122u));
    TestPrimitiveParsing(std::string("\x44\x33\x22\x11", 4), std::uint32_t(0x11223344u));
    TestPrimitiveParsing(std::string("\x88\x77\x66\x55\x44\x33\x22\x11", 8), std::uint64_t(0x1122334455667788llu));
    TestPrimitiveParsing(std::string("\xff", 1), std::int8_t(-1));
    TestPrimitiveParsing(std::string("\xff\xff", 2), std::int16_t(-1));
    TestPrimitiveParsing(std::string("\xff\xff\xff\xff", 4), std::int32_t(-1));
    TestPrimitiveParsing(std::string("\xff\xff\xff\xff\xff\xff\xff\xff", 8), std::int64_t(-1));
    TestPrimitiveParsing(std::string("\x01", 1), true);
    TestPrimitiveParsing(std::string("\x00\x00\xe0\x3f", 4), 1.75f);
    TestPrimitiveParsing(std::string("\x00\x00\x00\x00\x00\x00\x0c\xc0", 8), -3.5);
}

TEST_F(ProtocolOneTestFixture, ReadValue_String_CorrectlyParsed)
{
    const std::string input("\x05\x00\x00\x00\x00\x00\x00\x00Hello",
        sizeof(std::uint64_t) + std::strlen("Hello"));
    const std::string expectedResult("Hello");

    std::string result;

    {
        naranja::streams::MemoryStream memoryStream(SmallCacheSize);
        naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);
        memoryStream.Write(input.data(), input.size());

        auto protocol = std::make_shared<naranja::protocol::one::ObjectReader>(bufferedInputStream);
        protocol->ReadValue("", result);
    }
    
    ASSERT_TRUE(result == expectedResult);

}

TEST_F(ProtocolOneTestFixture, ReadValue_Binary_CorrectlyParsed)
{
    const std::string input("\x05\x00\x00\x00\x00\x00\x00\x00Hello",
        sizeof(std::uint64_t) + std::strlen("Hello"));
    const std::vector<char> expectedResult{'H', 'e', 'l', 'l', 'o'};

    std::vector<char> result;

    {
        naranja::streams::MemoryStream memoryStream(SmallCacheSize);
        naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);
        memoryStream.Write(input.data(), input.size());

        auto protocol = std::make_shared<naranja::protocol::one::ObjectReader>(bufferedInputStream);
        protocol->ReadValue("", result);
    }
    
    for(std::size_t i = 0; i < expectedResult.size(); ++i)
    {
        ASSERT_EQ(result[i], expectedResult[i]);
    }
}

TEST_F(ProtocolOneTestFixture, WriteValue_PrimitiveTypes_CorrectlySerialized)
{
    TestPrimitiveSerialization(std::uint8_t(0x11u), std::string("\x11", 1));
    TestPrimitiveSerialization(std::uint16_t(0x1122u), std::string("\x22\x11", 2));
    TestPrimitiveSerialization(std::uint32_t(0x11223344u), std::string("\x44\x33\x22\x11", 4));
    TestPrimitiveSerialization(std::uint64_t(0x1122334455667788llu), std::string("\x88\x77\x66\x55\x44\x33\x22\x11", 8));
    TestPrimitiveSerialization(std::int8_t(-1), std::string("\xff", 1));
    TestPrimitiveSerialization(std::int16_t(-1), std::string("\xff\xff", 2));
    TestPrimitiveSerialization(std::int32_t(-1), std::string("\xff\xff\xff\xff", 4));
    TestPrimitiveSerialization(std::int64_t(-1), std::string("\xff\xff\xff\xff\xff\xff\xff\xff", 8));
    TestPrimitiveSerialization(true, std::string("\x01", 1));
    TestPrimitiveSerialization(1.75f, std::string("\x00\x00\xe0\x3f", 4));
    TestPrimitiveSerialization(-3.5, std::string("\x00\x00\x00\x00\x00\x00\x0c\xc0", 8));
}

TEST_F(ProtocolOneTestFixture, WriteValue_String_CorrectlySerialized)
{
    const std::string expectedResult("\x05\x00\x00\x00\x00\x00\x00\x00Hello",
        sizeof(std::uint64_t) + std::strlen("Hello"));
    const std::string input("Hello");

    naranja::streams::MemoryStream memoryStream(SmallCacheSize);
    {
        naranja::tests::BufferedOutputStream bufferedOutputStream(memoryStream);
        auto objectWriter = std::make_shared<naranja::protocol::one::ObjectWriter>(bufferedOutputStream);
        objectWriter->WriteValue("", input);
    }

    std::string result(SmallCacheSize, 0);
    const auto resultSize = memoryStream.TryRead(&result[0], result.size());
    result.resize(resultSize);

    ASSERT_TRUE(result == expectedResult);
}

TEST_F(ProtocolOneTestFixture, WriteValue_Binary_CorrectlySerialized)
{
    const std::string expectedResult("\x05\x00\x00\x00\x00\x00\x00\x00Hello",
        sizeof(std::uint64_t) + std::strlen("Hello"));
    const std::vector<char> input{'H', 'e', 'l', 'l', 'o'};

    naranja::streams::MemoryStream memoryStream(SmallCacheSize);
    {
        naranja::tests::BufferedOutputStream bufferedOutputStream(memoryStream);
        auto objectWriter = std::make_shared<naranja::protocol::one::ObjectWriter>(bufferedOutputStream);
        objectWriter->WriteValue("", input);
    }

    std::string result(SmallCacheSize, 0);
    const auto resultSize = memoryStream.TryRead(&result[0], result.size());
    result.resize(resultSize);

    ASSERT_TRUE(result == expectedResult);
}

TEST_F(ProtocolOneTestFixture, ReadList_IntList_AllValuesProvided)
{
    const std::string encodedList("\x02\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff", sizeof(std::int32_t) * 3);
    const std::size_t expectedListSize = 2;
    const std::int32_t expectedListValue = -1;

    naranja::streams::MemoryStream memoryStream(SmallCacheSize);
    memoryStream.Write(encodedList.data(), encodedList.size());
    naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);
    auto protocol = std::make_shared<naranja::protocol::one::ObjectReader>(bufferedInputStream);

    std::vector<std::int32_t> result;

    std::size_t resultListLength = 0;
    auto listObjectReader = protocol->ReadList("", resultListLength);
    result.resize(resultListLength);

    for (size_t i = 0; i < result.size(); ++i)
    {
        listObjectReader->ReadValue("", result[i]);
    }

    ASSERT_EQ(result.size(), expectedListSize);
    ASSERT_EQ(result[0], expectedListValue);
    ASSERT_EQ(result[1], expectedListValue);
}

TEST_F(ProtocolOneTestFixture, WriteList_IntList_AllValuesWritten)
{
    const std::string expectedResult("\x02\x00\x00\x00" "\xff\xff\xff\xff" "\xff\xff\xff\xff", sizeof(std::int32_t) * 3);
    
    std::string result;
    naranja::streams::MemoryStream memoryStream(SmallCacheSize);
    {
        naranja::tests::BufferedOutputStream bufferedOutputStream(memoryStream);
        auto protocol = std::make_shared<naranja::protocol::one::ObjectWriter>(bufferedOutputStream);
        auto listObjectWriter = protocol->WriteList("", 2);
        listObjectWriter->WriteValue("", std::int32_t(-1));
        listObjectWriter->WriteValue("", std::int32_t(-1));
    }
    
    result.resize(SmallCacheSize);
    const auto resultSize = memoryStream.TryRead(&result[0], result.size());
    result.resize(resultSize);

    ASSERT_TRUE(result == expectedResult);
}

TEST_F(ProtocolOneTestFixture, WriteObject_NestedObjects_ObjectsSerialized)
{
    const std::string expectedResult("\xff\xff\xff\xff" "\xff\xff\xff\xff", sizeof(std::int32_t) * 2);
    
    std::string result;
    naranja::streams::MemoryStream memoryStream(SmallCacheSize);
    {
        naranja::tests::BufferedOutputStream bufferedOutputStream(memoryStream);
        auto protocol = std::make_shared<naranja::protocol::one::ObjectWriter>(bufferedOutputStream);
        
        protocol->WriteValue("", std::int32_t(-1));
        auto nestedObjectWriter = protocol->WriteObject("");
        nestedObjectWriter->WriteValue("", std::int32_t(-1));
    }

    result.resize(SmallCacheSize);
    const auto resultSize = memoryStream.TryRead(&result[0], result.size());
    result.resize(resultSize);

    ASSERT_TRUE(result == expectedResult);
}

TEST_F(ProtocolOneTestFixture, ReadObject_NestedObjects_ObjectsParsed)
{
    const std::string input("\xff\xff\xff\xff" "\xff\xff\xff\xff", sizeof(std::int32_t) * 2);
    const std::int32_t expectedValue = -1;

    naranja::streams::MemoryStream memoryStream(SmallCacheSize);
    memoryStream.Write(input.data(), input.size());
    naranja::tests::BufferedInputStream bufferedInputStream(memoryStream);
    auto objectReader = std::make_shared<naranja::protocol::one::ObjectReader>(bufferedInputStream);

    std::int32_t value1 = 0;
    objectReader->ReadValue("", value1);

    auto nestedObjectReader = objectReader->ReadObject("");
    std::int32_t value2 = 0;
    nestedObjectReader->ReadValue("", value2);

    ASSERT_EQ(value1, expectedValue);
    ASSERT_EQ(value2, expectedValue);
}

