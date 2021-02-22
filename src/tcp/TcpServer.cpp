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

gram::TcpServer::TcpServer()
{
    ServerId = createId();
}

gram::TcpServer::~TcpServer()
{
}

gram::TcpServer* gram::TcpServer::PromptAndCreateNewServer()
{
    int port = 0;
    char name[TcpServer::NAME_LENGTH];
    memset(name, 0, TcpServer::NAME_LENGTH);

    std::cout << "Port (0 for std port): ";

    if (!(std::cin >> port))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        throw GramException("Error setting port");
    }  

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Name (optional, 50 chars): ";
    std::cin.getline(name, TcpServer::NAME_LENGTH);

    TcpServer* server = new TcpServer();
    server->ServerName = name;
    server->Type = TCP;

    if (port == 0)
        port = STANDARD_PORT;

    server->Port = port;

    return server;
}

std::string gram::TcpServer::createId()
{
    char str[UUID_STR_LEN];
    uuid_t uuid;

    uuid_generate(uuid);
    uuid_unparse(uuid, str);
    uuid_clear(uuid);

    std::string id("TCP_" + std::string(str).substr(0, 4));

    return id;
}

void gram::TcpServer::Start()
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    setSocketOptions();

    address.sin_family = AF_INET;
    address.sin_port = htons(STANDARD_PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    int bound = bind(socketFd, (struct sockaddr *)&address, sizeof(address));

    if (bound == -1)
        throw GramException("Error binding address -> " + std::string(strerror(errno)));

    int listening = listen(socketFd, LISTEN_BACKLOG);

    if (listening == -1)
        throw GramException("Error starting to listen -> " + std::string(strerror(errno)));

    waitForConnections();
}

void gram::TcpServer::setSocketOptions()
{
    int optVal = 1;
    int setSockOpt = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(socketFd));

    if (setSockOpt == -1)
    {
        close(socketFd);
        throw GramException("Error setting socket option -> " + std::string(strerror(errno)));
    }
}

void gram::TcpServer::Stop()
{
    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing server socket -> " + std::string(strerror(errno)));

    WaitThread.detach();
    for (int i = 0; i < ConnectionThreads.size(); i++)
        ConnectionThreads.at(i).detach();
}

void gram::TcpServer::waitForConnections()
{
    WaitThread = std::thread(
        [&]() {

            timeval timeout;
            fd_set readSocket;
            FD_ZERO(&readSocket);
            FD_SET(socketFd, &readSocket);

            while(true)
            {
                timeout.tv_usec = TcpServer::SELECT_TIMEOUT_MICROSECONDS;

                int sel = select(socketFd + 1, &readSocket, NULL, NULL, &timeout);

                if (sel == -1)
                    break;

                if (sel == 0)
                {
                    int readable = fcntl(socketFd, F_GETFD);

                    if (readable == -1)
                        break;

                    continue;
                }

                socklen_t sz = sizeof(address);
                int acceptedSocketFd = accept(socketFd, (struct sockaddr *)&address, (socklen_t *)&sz);

                if (acceptedSocketFd == -1)
                    return;

                addConnection(acceptedSocketFd);
            }
        });
}

void gram::TcpServer::addConnection(int socketFd)
{
    std::thread connection = std::thread(
        [=]() {
            char buffer[TcpServer::BUFFER_SIZE];

            while (true)
            {
                ssize_t readBytes = read(socketFd, buffer, TcpServer::BUFFER_SIZE);

                if (readBytes == -1 || readBytes == 0)
                    break;

                receivedHandler(std::string(buffer));
                memset(buffer, 0, TcpServer::BUFFER_SIZE);
            }

            close(socketFd);
        });

    ConnectionThreads.push_back(std::move(connection));
}

void gram::TcpServer::receivedHandler(std::string message)
{
    // TODO:
}