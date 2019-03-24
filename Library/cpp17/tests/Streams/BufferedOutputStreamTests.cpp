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
    auto memoryStream = std::make_shared<std::stringstream>();
    const std::size_t cacheSize = 5;

    auto outputStream = std::make_shared<OutputStreamMock>();
    auto bufferedOutputStream = Rpc2::Streams::BufferedOutputStream::Create(outputStream, cacheSize);

    EXPECT_CALL(*outputStream, Write(::testing::_, 10)).Times(1);

    std::string testValue = "HelloWorld";
    bufferedOutputStream->Write(testValue.data(), testValue.size());
}

TEST_F(BufferedOutputStreamTestFixture, Write_NonEmptyCachePlusRequestLargerThanCache_FlushedAndWritten)
{
    auto memoryStream = std::make_shared<std::stringstream>();
    const std::size_t cacheSize = 5;

    auto outputStream = std::make_shared<OutputStreamMock>();
    auto bufferedOutputStream = Rpc2::Streams::BufferedOutputStream::Create(outputStream, cacheSize);

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

    auto outputStream = std::make_shared<OutputStreamMock>();
    auto bufferedOutputStream = Rpc2::Streams::BufferedOutputStream::Create(outputStream, cacheSize);

    std::string testValue = "HelloWorld";
    EXPECT_CALL(*outputStream, Write(::testing::_, ::testing::_)).Times(0);

    bufferedOutputStream->Write(testValue.data(), testValue.size());
}

TEST_F(BufferedOutputStreamTestFixture, Flush_DataInCache_DataWritten)
{
    auto memoryStream = std::make_shared<std::stringstream>();
    const std::size_t cacheSize = 20;

    auto outputStream = std::make_shared<OutputStreamMock>();
    auto bufferedOutputStream = Rpc2::Streams::BufferedOutputStream::Create(outputStream, cacheSize);

    std::string testValue = "HelloWorld";
    EXPECT_CALL(*outputStream, Write(::testing::_, testValue.size())).Times(1);

    bufferedOutputStream->Write(testValue.data(), testValue.size());
    bufferedOutputStream->Flush();
}
