#include <boost/coroutine2/all.hpp>
#include <gmock/gmock.h>
#include <iostream>
#include <naranja/streams/YieldingInputStream.hpp>

class CoroutineTestFixture : public testing::Test
{
};

TEST_F(CoroutineTestFixture, test1)
{
    boost::coroutines2::coroutine<void>::pull_type coro([](boost::coroutines2::coroutine<void>::push_type& coro) {
        std::cout << "A" << std::endl;
        //auto yield = [&coro]() { coro(); };
        //auto inputStream = std::make_shared<naranja::streams::YieldingInputStream>(yield, nullptr);
    });

    std::cout << "1" << std::endl;
    if(coro)coro();
    std::cout << "2" << std::endl;
    if(coro)coro();
    std::cout << "3" << std::endl;
    //coro();
    std::cout << "4" << std::endl;
}

