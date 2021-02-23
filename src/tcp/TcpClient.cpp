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

#include "../../include/tcp/TcpClient.hpp"

gram::TcpClient::TcpClient()
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));
}

gram::TcpClient::TcpClient(std::string endpointIpOrName, int port)
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    EndpointIpOrName = endpointIpOrName;
    Port = port;
}

gram::TcpClient::~TcpClient()
{
    Close();
}

void gram::TcpClient::Open()
{
    struct addrinfo* addresses;

    int gotInfo = getaddrinfo(EndpointIpOrName.c_str(), std::to_string(Port).c_str(), nullptr, &addresses);

    if (gotInfo != 0)
        throw GramException("Error getting address information -> " + std::string(gai_strerror(gotInfo)));
    
    struct addrinfo* target = addresses->ai_next;

    int connected = connect(socketFd, target->ai_addr, target->ai_addrlen);

    if (connected == -1)
        throw GramException("Error connecting to target -> " + std::string(strerror(errno)));

    IsOpen = true;
}

void gram::TcpClient::Close()
{
    if (socketFd == 0)
        return;        
    
    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing socket -> " + std::string(strerror(errno)));

    socketFd = 0;
    IsOpen = false;
}