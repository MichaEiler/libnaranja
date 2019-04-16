#include <gmock/gmock.h>
#include <memory>
#include <naranja/streams/BufferedOutputStream.hpp>
#include <naranja/streams/AdaptiveMemoryStream.hpp>
#include <sstream>
#include <string>

class OutputStreamMock : public naranja::streams::IOutputStream {
public:
    MOCK_METHOD2(Write, void(const char*, const std::size_t));
    MOCK_METHOD0(Flush, void());
};

class BufferedOutputStreamTestFixture : public testing::Test
{
};

TEST_F(BufferedOutputStreamTestFixture, Write_EmptyCacheAndRequestLargerThanCache_ImmediateWrite)
{
    const std::size_t cacheSize = 5;
    OutputStreamMock outputStream;
    naranja::streams::BufferedOutputStream bufferedOutputStream(outputStream, cacheSize);

    EXPECT_CALL(outputStream, Write(::testing::_, 10)).Times(1);

    std::string testValue = "HelloWorld";
    bufferedOutputStream.Write(testValue.data(), testValue.size());
}

TEST_F(BufferedOutputStreamTestFixture, Write_NonEmptyCachePlusRequestLargerThanCache_FlushedAndWritten)
{
    const std::size_t cacheSize = 5;
    OutputStreamMock outputStream;
    naranja::streams::BufferedOutputStream bufferedOutputStream(outputStream, cacheSize);

    {
        ::testing::InSequence queue;
        EXPECT_CALL(outputStream, Write(::testing::_, 3)).Times(1);
        EXPECT_CALL(outputStream, Write(::testing::_, 10)).Times(1);
    }

    std::string testValue = "HelloWorld";
    bufferedOutputStream.Write(testValue.data(), 3);
    bufferedOutputStream.Write(testValue.data(), testValue.size());
}

TEST_F(BufferedOutputStreamTestFixture, Write_RequestSmallerThanCacheSize_NoDataWritten)
{
    naranja::streams::AdaptiveMemoryStream memoryStream;
    const std::size_t cacheSize = 20;
    naranja::streams::BufferedOutputStream bufferedOutputStream(memoryStream, cacheSize);

    std::string testValue = "HelloWorld";
    bufferedOutputStream.Write(testValue.data(), testValue.size());
    
    ASSERT_EQ(0, memoryStream.AvailableBytes());

    bufferedOutputStream.Flush();
    ASSERT_EQ(testValue.size(), memoryStream.AvailableBytes());
}

TEST_F(BufferedOutputStreamTestFixture, Write_RequestSmallerThanCacheSize_FlushedOnDestruction)
{
    naranja::streams::AdaptiveMemoryStream memoryStream;
    std::string testValue = "HelloWorld";

    {
        const std::size_t cacheSize = 20;
        naranja::streams::BufferedOutputStream bufferedOutputStream(memoryStream, cacheSize);    
        bufferedOutputStream.Write(testValue.data(), testValue.size());
    }

    std::string result;
    result.resize(testValue.size());
    memoryStream.TryRead(&result[0], testValue.size());

    ASSERT_STREQ(result.c_str(), testValue.c_str());
}

TEST_F(BufferedOutputStreamTestFixture, Flush_DataInCache_DataWritten)
{
    const std::size_t cacheSize = 20;
    OutputStreamMock outputStream;
    naranja::streams::BufferedOutputStream bufferedOutputStream(outputStream, cacheSize);

    std::string testValue = "HelloWorld";
    EXPECT_CALL(outputStream, Write(::testing::_, testValue.size())).Times(1);

    bufferedOutputStream.Write(testValue.data(), testValue.size());
    bufferedOutputStream.Flush();
}
