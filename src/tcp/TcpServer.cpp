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

#include "../../include/tcp/TcpServer.hpp"

TcpServer::TcpServer()
{
}

TcpServer::~TcpServer()
{
    Stop();
}

void TcpServer::Start()
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

      if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    address.sin_family = AF_INET;
    address.sin_port = htons(STANDARD_PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    int bound = bind(socketFd, (struct sockaddr*)&address, sizeof(address));

    if (bound == -1)
        throw GramException("Error binding address -> " + std::string(strerror(errno)));

    int listening = listen(socketFd, LISTEN_BACKLOG);

    if (listening == -1)
        throw GramException("Error starting to listen -> " + std::string(strerror(errno)));

    waitForConnections();
}

void TcpServer::Start(int bindPort)
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

      if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    address.sin_family = AF_INET;
    address.sin_port = htons(bindPort);
    address.sin_addr.s_addr = INADDR_ANY;

    int bound = bind(socketFd, (struct sockaddr*)&address, sizeof(address));

    if (bound == -1)
        throw GramException("Error binding address -> " + std::string(strerror(errno)));

    int listening = listen(socketFd, LISTEN_BACKLOG);

    if (listening == -1)
        throw GramException("Error starting to listen -> " + std::string(strerror(errno)));

    waitForConnections();
}

void TcpServer::Stop()
{
    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing server socket -> " + std::string(strerror(errno)));

    WaitThread.detach();
    for(int i = 0; i < ConnectionThreads.size(); i++)
        ConnectionThreads.at(i).detach();

    socketFd = 0;
}

void TcpServer::waitForConnections()
{
    WaitThread = std::thread(
        [&]
        ()
        {
            socklen_t sz = sizeof(address);
            int acceptedSocketFd = accept(socketFd, (struct sockaddr*)&address, (socklen_t*)&sz);

            if (acceptedSocketFd == -1)
                throw GramException("Error accepting incoming connection -> " + std::string(strerror(errno)));

            addConnection(acceptedSocketFd);
        });
}

void TcpServer::addConnection(int socketFd)
{
    std::thread connection = std::thread(
        [=]
        ()
        {
            char buffer[TcpServer::BUFFER_SIZE];

            while(true)
            {
                ssize_t readBytes = read(socketFd, buffer, TcpServer::BUFFER_SIZE);

                if (readBytes == -1)
                    throw GramException("Error reading bytes -> " + std::string(strerror(errno)));

                if (readBytes == 0)
                    break;

                receivedHandler(std::string(buffer));
                memset(buffer, 0, TcpServer::BUFFER_SIZE);
            }
        });

    ConnectionThreads.push_back(std::move(connection));
}