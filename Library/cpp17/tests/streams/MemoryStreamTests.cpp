#include <gmock/gmock.h>
#include <naranja/streams/MemoryStream.hpp>
#include <thread>

#include <iostream>

class MemoryStreamTestFixture : public testing::Test
{
};

TEST_F(MemoryStreamTestFixture, Write_LargerThanCacheSize_CapacityIncreased)
{
    const std::string data("HelloWorld");
    naranja::streams::MemoryStream stream(data.size() >> 1);
    
    ASSERT_TRUE(stream.Capacity() < data.size());
    stream.Write(data.data(), data.size());
    ASSERT_TRUE(stream.Capacity() >= data.size());
}

TEST_F(MemoryStreamTestFixture, Write_LargerThanCacheSize_WrittenDataComplete)
{
    const std::string data("HelloWorld");
    naranja::streams::MemoryStream stream(data.size() >> 1);

    stream.Write(data.data(), data.size());
    ASSERT_TRUE(stream.AvailableBytes() == data.size());
}

TEST_F(MemoryStreamTestFixture, Write_LargerThanCacheSize_WrittenDataValid)
{
    const std::string data("HelloWorld");
    naranja::streams::MemoryStream stream(data.size() >> 1);

    stream.Write(data.data(), data.size());
    
    std::string result;
    result.resize(data.size() * 2, '\0');

    auto bytesConsumed = stream.TryRead(&result[0], result.size());
    result.resize(bytesConsumed);

    ASSERT_TRUE(result == data);
}

TEST_F(MemoryStreamTestFixture, Write_NotAtStartAndLargerThanTillEnd_DataCorrectlyWrappedAround)
{
    const std::string data("HelloWorld");
    naranja::streams::MemoryStream stream(14);
    stream.Write(data.data(), data.size());
    
    std::string result;
    result.resize(data.size(), '\0');
    stream.TryRead(&result[0], result.size());

    stream.Write(data.data(), data.size());
    stream.TryRead(&result[0], result.size());

    ASSERT_TRUE(result == data);
}

TEST_F(MemoryStreamTestFixture, Read_NotEnoughDataAvailable_ReturnsAvailableData)
{
    const std::string data("HelloWorld");
    naranja::streams::MemoryStream stream(20);
    stream.Write(data.data(), data.size());

    std::string result;
    result.resize(data.size(), '\0');

    auto bytesConsumed = stream.TryRead(&result[0], 200);
    result.resize(bytesConsumed);

    ASSERT_TRUE(result == data);
}

TEST_F(MemoryStreamTestFixture, Read_MoreThanRequestedAvailable_ReturnsRequestedData)
{
    const std::string data("HelloWorld");
    naranja::streams::MemoryStream stream(20);
    stream.Write(data.data(), data.size());

    std::string result;
    result.resize(data.size(), '\0');

    auto bytesConsumed = stream.TryRead(&result[0], 5);
    result.resize(bytesConsumed);

    ASSERT_TRUE(result == "Hello");
}

TEST_F(MemoryStreamTestFixture, Read_NoDataAvailable_ReturnsZero)
{
    const std::string data("HelloWorld");
    naranja::streams::MemoryStream stream(20);

    auto bytesConsumed = stream.TryRead(nullptr, 5);

    ASSERT_EQ(0, bytesConsumed);
}

TEST_F(MemoryStreamTestFixture, Read_DataWrappedAround_ResultingDataValid)
{
    const std::string data("HelloWorld");
    const std::string data2("CountryRoads");
    naranja::streams::MemoryStream stream(15);

    std::string result;
    result.resize(stream.Capacity(), '\0');

    stream.Write(data.data(), data.size());
    stream.TryRead(&result[0], data.size());
    stream.Write(data2.data(), data2.size());
    
    auto bytesConsumed = stream.TryRead(&result[0], stream.Capacity());
    result.resize(bytesConsumed);

    ASSERT_TRUE(result == data2);
}
