#include <gmock/gmock.h>
#include <naranja/streams/RigidMemoryStream.hpp>
#include <thread>

#include <iostream>

class MemoryStreamTestFixture : public testing::Test
{
};

TEST_F(MemoryStreamTestFixture, Write_FitsIntoCache_DataWritten)
{
    const std::string testValue("HelloWorld");

    naranja::streams::RigidMemoryStream memoryStream;
    memoryStream.Write(testValue.c_str(), testValue.size());

    std::string result;
    result.resize(10);

    ASSERT_EQ(memoryStream.TryRead(&result[0], result.size()), testValue.size());
    ASSERT_STREQ(result.c_str(), testValue.c_str());
}

TEST_F(MemoryStreamTestFixture, Write_StreamClosed_ThrowsException)
{
    naranja::streams::RigidMemoryStream memoryStream;
    memoryStream.Close();
    ASSERT_THROW(memoryStream.Write(nullptr, 0), naranja::exceptions::StreamClosed);
}

TEST_F(MemoryStreamTestFixture, Write_LargerThanCache_DataProcessed)
{
    const std::size_t cacheSize = 33;
    const std::size_t dataToWrite = 400;

    naranja::streams::RigidMemoryStream memoryStream(cacheSize);

    std::size_t consumedBytes = 0;
    std::thread consumerThread([&](){
        try
        {
            std::vector<char> readBuffer(10, 0);
            for (;;)
            {
                consumedBytes += memoryStream.TryRead(&readBuffer[0], readBuffer.size());
            }    
        }
        catch(const naranja::exceptions::StreamClosed&)
        { } 
    });

    std::vector<char> inputBuffer(dataToWrite, 0);
    memoryStream.Write(inputBuffer.data(), inputBuffer.size());
    memoryStream.Close();

    consumerThread.join();

    ASSERT_EQ(dataToWrite, consumedBytes);
}

TEST_F(MemoryStreamTestFixture, Write_LargerThanCache_DataValid)
{
    const std::size_t cacheSize = 7;

    std::vector<char> referenceData(81, 0);
    for (std::size_t i = 0; i < referenceData.size(); ++i)
    {
        referenceData[i] = static_cast<char>(i);
    }

    naranja::streams::RigidMemoryStream memoryStream(cacheSize);

    std::vector<char> result(referenceData.size(), 0);
    std::size_t consumedBytes = 0;
    std::thread consumerThread([&](){
        try
        {
            for (;;)
            {
                result.resize(result.size() + 10);
                consumedBytes += memoryStream.TryRead(&result[consumedBytes], result.size() - consumedBytes);
            }    
        }
        catch(const naranja::exceptions::StreamClosed&)
        { } 
    });

    memoryStream.Write(referenceData.data(), referenceData.size());
    memoryStream.Close();

    consumerThread.join();

    for (std::size_t i = 0; i < referenceData.size(); ++i)
    {
        ASSERT_EQ(referenceData[i], result[i]);
    }
}

TEST_F(MemoryStreamTestFixture, Write_LargerThanCache_BlocksUntilWriteCompleted)
{
    const std::size_t cacheSize = 80;
    naranja::streams::RigidMemoryStream memoryStream(cacheSize);

    bool dataWritten = false;
    std::thread producerThread([&](){
        std::vector<char> buffer(100, 0);
        memoryStream.Write(buffer.data(), buffer.size());
        dataWritten = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_FALSE(dataWritten);

    std::vector<char> tmp(cacheSize, 0);
    memoryStream.TryRead(&tmp[0], tmp.size());
    producerThread.join();

    ASSERT_TRUE(dataWritten);
}

TEST_F(MemoryStreamTestFixture, Read_WriteProvidesPartialData_ReadReturns)
{
    const std::size_t cacheSize = 80;
    naranja::streams::RigidMemoryStream memoryStream(cacheSize);

    std::size_t bytesRead = 0;
    std::thread consumerThread([&](){
        std::vector<char> buffer(100, 0);
        bytesRead = memoryStream.TryRead(&buffer[0], buffer.size());
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(bytesRead, 0);

    std::vector<char> inputData(10, 0);
    memoryStream.Write(inputData.data(), inputData.size());
    consumerThread.join();

    ASSERT_EQ(bytesRead, inputData.size());
}
