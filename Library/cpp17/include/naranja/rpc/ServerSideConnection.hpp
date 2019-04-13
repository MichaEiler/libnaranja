#pragma once

#include <boost/asio.hpp>
#include <boost/coroutine2/all.hpp>
#include <memory>

namespace naranja
{
    namespace rpc
    {
        class ServerSideConnection
        {
        public:
            explicit ServerSideConnection(boost::asio::io_service& service);

        private:
            boost::asio::io_service& _service;
        };
    }
}