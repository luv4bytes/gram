/* Copyright (c) 2021 Lukas Pfeifer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "../../include/udp/UdpServer.hpp"

gram::UdpServer::UdpServer()
{
    ServerId = createId();
}

gram::UdpServer::~UdpServer()
{
    Stop();
}

std::string gram::UdpServer::createId()
{
    char str[UUID_STR_LEN];
    uuid_t uuid;

    uuid_generate(uuid);
    uuid_unparse(uuid, str);
    uuid_clear(uuid);

    std::string id("UDP_" + std::string(str).substr(0, 4));

    return id;
}

void gram::UdpServer::Start()
{
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);

      if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    address.sin_family = AF_INET;
    address.sin_port = htons(STANDARD_PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    int bound = bind(socketFd, (struct sockaddr*)&address, sizeof(address));

    if (bound == -1)
        throw GramException("Error binding address -> " + std::string(strerror(errno)));

    waitForDatagrams();
}

void gram::UdpServer::Start(int bindPort)
{
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);

      if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    address.sin_family = AF_INET;
    address.sin_port = htons(bindPort);
    address.sin_addr.s_addr = INADDR_ANY;

    int bound = bind(socketFd, (struct sockaddr*)&address, sizeof(address));

    if (bound == -1)
        throw GramException("Error binding address -> " + std::string(strerror(errno)));
        
    waitForDatagrams();
}

void gram::UdpServer::Stop()
{
    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing server socket -> " + std::string(strerror(errno)));

    WaitThread.detach();
    socketFd = 0;
}

int gram::UdpServer::GetListenerPort()
{
    if (socketFd == 0)
        return -1;

    struct sockaddr_in addr;
    socklen_t sz = sizeof(addr);

    int port = getsockname(socketFd, (struct sockaddr*) &addr, &sz);

    return ntohs(addr.sin_port);
}

void gram::UdpServer::waitForDatagrams()
{
    WaitThread = std::thread(
        [&]
        ()
        {
            socklen_t sz = sizeof(address);
            char buffer[UdpServer::BUFFER_SIZE];

            ssize_t received = recv(socketFd, buffer, UdpServer::BUFFER_SIZE, 0);

            if (received == -1)
                throw GramException("Error receiving datagram -> " + std::string(strerror(errno)));

            receivedHandler(std::string(buffer));
        });
}