/*#include <naranja/rpc/ClientSideConnection.hpp>
#include <naranja/rpc/ServerSideConnection.hpp>
#include <naranja/rpc/Server.hpp>
#include <naranja/protocol/one/Protocol.hpp>
#include <gmock/gmock.h>
#include <iostream>

#include "EchoService.hpp"

class NetworkTestFixture : public testing::Test
{
};

TEST_F(NetworkTestFixture,ServerClientTest1)
{
    auto service = std::make_shared<EchoService>();
    auto server = std::make_shared<naranja::rpc::Server>(service, 50123);
    server->Start();

    auto client = std::make_shared<naranja::rpc::ClientSideConnection>();
    client->Connect("127.0.0.1", 50123);

    for(;;)
    {
        std::string input;
        std::cin >> input;

        if (input == "exit")
            break;

        client->Write(input.data(), input.size());
    }

    client->Close();
}*/