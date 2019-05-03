#include <naranja/rpc/Server.hpp>
#include <naranja/rpc/ClientSideConnection.hpp>
#include <naranja/core/Exceptions.hpp>
#include <chrono>
#include <future>
#include <gmock/gmock.h>
#include <thread>

#include "common/EchoBroker.hpp"

constexpr std::uint16_t NetworkPortForTests = 50674u;

class ExpectTimeoutException : public std::exception {};

class ConnectionTestFixture : public testing::Test
{
protected:
    template <typename TExpect, typename F>
    void TimedExpect(const TExpect& expectedResult, F&& func, const std::chrono::milliseconds& timeout)
    {
        const auto start = std::chrono::system_clock::now();
        do
        {
            auto result = func();
            if (result == expectedResult)
            {
                return;
            }
            const auto end = std::chrono::system_clock::now();

            if ((end - start) > timeout)
            {
                throw ExpectTimeoutException();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (true);
    }

    /*template <typename F>
    void TimedExpectThrow(F&& func, const std::chrono::milliseconds& timeout)
    {
        const auto start = std::chrono::system_clock::now();
        do
        {
            func();
            const auto end = std::chrono::system_clock::now();
            if ((end - start) > timeout)
            {
                throw ExpectTimeoutException();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (true);
        
    }*/
};

TEST_F(ConnectionTestFixture, CloseClient_AfterClientConnectionUp_ServerRemovesConnection)
{
    auto brokerFactory = std::make_shared<naranja::tests::EchoBrokerFactory>();
    auto server = std::make_shared<naranja::rpc::Server>(brokerFactory, NetworkPortForTests);
    auto client = std::make_shared<naranja::rpc::ClientSideConnection>(brokerFactory->Create());

    server->Start();
    ASSERT_EQ(0, server->NumberOfConnections());

    client->Connect("127.0.0.1", NetworkPortForTests);
    TimedExpect(1, [&](){ return server->NumberOfConnections(); }, std::chrono::milliseconds(1000));

    client->Close();
    TimedExpect(0, [&](){ return server->NumberOfConnections(); }, std::chrono::milliseconds(1000));
}

/*TEST_F(ConnectionTestFixture, CloseServer_ConnectionEstablisheded_OnConnectionLostSignalled)
{
    auto service = std::make_shared<EchoService>();
    auto server = std::make_shared<naranja::rpc::Server>(service, NetworkPortForTests);
    auto client = std::make_shared<naranja::rpc::ClientSideConnection>();
    server->Start();

    auto disconnectSignalSent = std::make_shared<std::promise<void>>();
    auto disconnectSignalSentFuture = disconnectSignalSent->get_future();
    client->OnConnectionLost([promise = std::move(disconnectSignalSent)] () mutable { promise->set_value(); });
    client->Connect("127.0.0.1", NetworkPortForTests);

    server->Stop();
    server.reset();

    //ASSERT_EQ(std::future_status::ready, disconnectSignalSentFuture.wait_for(std::chrono::milliseconds(500)));
    disconnectSignalSentFuture.wait_for(std::chrono::milliseconds(3000));
    std::cout << "hello" << std::endl;

    client->Close();
    client.reset();

    ASSERT_NO_THROW(disconnectSignalSentFuture.get());
}*/

/*TEST_F(ConnectionTestFixture, ClientWrite_ConnectionDead_ThrowsConnectionLost)
{
    auto service = std::make_shared<EchoService>();
    auto server = std::make_shared<naranja::rpc::Server>(service, NetworkPortForTests);
    auto client = std::make_shared<naranja::rpc::ClientSideConnection>();
    server->Start();

    client->Connect("127.0.0.1", NetworkPortForTests);

    server->Stop();
    server.reset();

    ASSERT_THROW(TimedExpectThrow([&](){
        const std::string TestData("HelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorld");
        client->Write(TestData.data(), TestData.size());
     }, std::chrono::milliseconds(10000)), naranja::exceptions::ConnectionClosed);
}*/


