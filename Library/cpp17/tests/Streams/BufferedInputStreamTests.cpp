#include <gmock/gmock.h>
#include <memory>
#include <Rpc2/Streams/BufferedInputStream.hpp>
#include <Rpc2/Streams/StdInputStream.hpp>
#include <sstream>
#include <string>

class BufferedInputStreamTestFixture : public testing::Test
{
};

TEST_F(BufferedInputStreamTestFixture, Peek_SingleCall_ReturnsData)
{
    auto memoryStream = std::make_shared<std::stringstream>();
    *memoryStream << "HelloWorld";
    
    auto stream = Rpc2::Streams::BufferedInputStream::Create(Rpc2::Streams::StdInputStream::Create(memoryStream));
    std::string result;
    result.resize(5);
    stream->Peek(&result[0], result.size());

    std::string expectedResult("Hello");
    ASSERT_STREQ(result.c_str(), expectedResult.c_str());
}

TEST_F(BufferedInputStreamTestFixture, Peek_MultipleCalls_AllReturnTheSameData)
{
    auto memoryStream = std::make_shared<std::stringstream>();
    *memoryStream << "HelloWorld";
    
    auto stream = Rpc2::Streams::BufferedInputStream::Create(Rpc2::Streams::StdInputStream::Create(memoryStream));
    std::string result;
    result.resize(5);
    stream->Peek(&result[0], result.size());

    for (int i = 0; i < 3; ++i)
    {
        std::string expectedResult("Hello");
        ASSERT_STREQ(result.c_str(), expectedResult.c_str());
    }
}

TEST_F(BufferedInputStreamTestFixture, Peek_RequestLargerThanCacheSize_InvalidArgumentThrown)
{
    const std::size_t cacheSize = 10;

    auto memoryStream = std::make_shared<std::stringstream>();
    auto stream = Rpc2::Streams::BufferedInputStream::Create(Rpc2::Streams::StdInputStream::Create(memoryStream), cacheSize);

    ASSERT_THROW(stream->Peek(nullptr, cacheSize + 1), std::invalid_argument);
}

TEST_F(BufferedInputStreamTestFixture, Peek_WrapAroundInCache_RequestedDataReturned)
{
    const std::string testValue("HelloWorld");

    auto memoryStream = std::make_shared<std::stringstream>();
    *memoryStream << testValue << testValue;

    const std::size_t cacheSize = 13;
    auto stream = Rpc2::Streams::BufferedInputStream::Create(Rpc2::Streams::StdInputStream::Create(memoryStream), cacheSize);

    std::string tmp;
    tmp.resize(testValue.size());
    stream->Read(&tmp[0], tmp.size());

    std::string result;
    result.resize(testValue.size());
    stream->Peek(&result[0], result.size());

    ASSERT_STREQ(result.c_str(), testValue.c_str());
}

TEST_F(BufferedInputStreamTestFixture, Read_NewStream_FollowedPeekWillReturnNextData)
{
    auto memoryStream = std::make_shared<std::stringstream>();
    *memoryStream << "HelloWorld";
    std::string result;
    
    auto stream = Rpc2::Streams::BufferedInputStream::Create(Rpc2::Streams::StdInputStream::Create(memoryStream));
    result.resize(5);
    stream->Read(&result[0], result.size());

    std::string expectedReadResult("Hello");
    ASSERT_STREQ(result.c_str(), expectedReadResult.c_str());

    result.resize(5);
    stream->Peek(&result[0], result.size());
    
    std::string expectedPeekResult("World");
    ASSERT_STREQ(result.c_str(), expectedPeekResult.c_str());
}

TEST_F(BufferedInputStreamTestFixture, Read_ReqeustLargerThanCacheSize_AllDataReturned)
{
    const std::string testValue("HelloWorld");

    auto memoryStream = std::make_shared<std::stringstream>();
    *memoryStream << testValue;
    
    const std::size_t cacheSize = 7;
    auto stream = Rpc2::Streams::BufferedInputStream::Create(Rpc2::Streams::StdInputStream::Create(memoryStream), cacheSize);

    std::string result;
    result.resize(testValue.size());
    stream->Read(&result[0], result.size());

    ASSERT_STREQ(result.c_str(), testValue.c_str());
}

TEST_F(BufferedInputStreamTestFixture, Read_WrapAroundInCache_RequestedDataReturned)
{
    const std::string testValue("HelloWorld");

    auto memoryStream = std::make_shared<std::stringstream>();
    *memoryStream << testValue << testValue;

    const std::size_t cacheSize = 13;
    auto stream = Rpc2::Streams::BufferedInputStream::Create(Rpc2::Streams::StdInputStream::Create(memoryStream), cacheSize);

    std::string tmp;
    tmp.resize(testValue.size());
    stream->Read(&tmp[0], tmp.size());

    std::string result;
    result.resize(testValue.size());
    stream->Read(&result[0], result.size());

    ASSERT_STREQ(result.c_str(), testValue.c_str());
}