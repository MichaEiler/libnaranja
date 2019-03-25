#include <gmock/gmock.h>
#include <memory>
#include <Rpc2/Streams/BufferedOutputStream.hpp>
#include <Rpc2/Streams/StdOutputStream.hpp>
#include <sstream>
#include <string>

class OutputStreamMock : public Rpc2::Streams::IOutputStream {
public:
    MOCK_METHOD2(Write, void(const char*, const std::size_t));
};

class BufferedOutputStreamTestFixture : public testing::Test
{
};

TEST_F(BufferedOutputStreamTestFixture, Write_EmptyCacheAndRequestLargerThanCache_ImmediateWrite)
{
    const std::size_t cacheSize = 5;
    auto outputStream = std::make_shared<OutputStreamMock>();
    auto bufferedOutputStream = std::make_shared<Rpc2::Streams::BufferedOutputStream>(outputStream, cacheSize);

    EXPECT_CALL(*outputStream, Write(::testing::_, 10)).Times(1);

    std::string testValue = "HelloWorld";
    bufferedOutputStream->Write(testValue.data(), testValue.size());
}

TEST_F(BufferedOutputStreamTestFixture, Write_NonEmptyCachePlusRequestLargerThanCache_FlushedAndWritten)
{
    const std::size_t cacheSize = 5;
    auto outputStream = std::make_shared<OutputStreamMock>();
    auto bufferedOutputStream = std::make_shared<Rpc2::Streams::BufferedOutputStream>(outputStream, cacheSize);

    {
        ::testing::InSequence queue;
        EXPECT_CALL(*outputStream, Write(::testing::_, 3)).Times(1);
        EXPECT_CALL(*outputStream, Write(::testing::_, 10)).Times(1);
    }

    std::string testValue = "HelloWorld";
    bufferedOutputStream->Write(testValue.data(), 3);
    bufferedOutputStream->Write(testValue.data(), testValue.size());
}

TEST_F(BufferedOutputStreamTestFixture, Write_RequestSmallerThanCacheSize_NoDataWritten)
{
    auto memoryStream = std::make_shared<std::stringstream>();
    const std::size_t cacheSize = 20;
    auto bufferedOutputStream = std::make_shared<Rpc2::Streams::BufferedOutputStream>(std::make_shared<Rpc2::Streams::StdOutputStream>(memoryStream), cacheSize);

    std::string testValue = "HelloWorld";
    bufferedOutputStream->Write(testValue.data(), testValue.size());

    const std::string result = memoryStream->str();
    const std::string expectedResult("");

    ASSERT_STREQ(result.c_str(), expectedResult.c_str());
}

TEST_F(BufferedOutputStreamTestFixture, Write_RequestSmallerThanCacheSize_FlushedOnDestruction)
{
    auto memoryStream = std::make_shared<std::stringstream>();
    std::string testValue = "HelloWorld";

    {
        const std::size_t cacheSize = 20;
        auto bufferedOutputStream = std::make_shared<Rpc2::Streams::BufferedOutputStream>(std::make_shared<Rpc2::Streams::StdOutputStream>(memoryStream), cacheSize);    
        bufferedOutputStream->Write(testValue.data(), testValue.size());
    }

    const std::string result = memoryStream->str();

    ASSERT_STREQ(result.c_str(), testValue.c_str());
}

TEST_F(BufferedOutputStreamTestFixture, Flush_DataInCache_DataWritten)
{
    const std::size_t cacheSize = 20;
    auto outputStream = std::make_shared<OutputStreamMock>();
    auto bufferedOutputStream = std::make_shared<Rpc2::Streams::BufferedOutputStream>(outputStream, cacheSize);

    std::string testValue = "HelloWorld";
    EXPECT_CALL(*outputStream, Write(::testing::_, testValue.size())).Times(1);

    bufferedOutputStream->Write(testValue.data(), testValue.size());
    bufferedOutputStream->Flush();
}
