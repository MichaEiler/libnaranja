#pragma once

#include <boost/asio.hpp>

#ifdef _MSC_VER
#include <Winsock2.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#endif

static void SetKeepAlive(boost::asio::ip::tcp::socket& socket)
{
    const int enable = 1;
    setsockopt(socket.native_handle(), SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));

    const int idle = 1;
    setsockopt(socket.native_handle(), IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(idle));

    const int interval = 1;
    setsockopt(socket.native_handle(), IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));

    const int retries = 3;
    setsockopt(socket.native_handle(), IPPROTO_TCP, TCP_KEEPCNT, &retries, sizeof(retries));
}

