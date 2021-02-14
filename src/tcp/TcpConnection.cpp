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

#include "../../include/tcp/TcpConnection.hpp"

TcpConnection::TcpConnection()
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));
}

TcpConnection::TcpConnection(std::string endpointIpOrName, int port)
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    EndpointIpOrName = endpointIpOrName;
    Port = port;
}

TcpConnection::~TcpConnection()
{
    Close();
}

void TcpConnection::Open()
{
    struct addrinfo* addresses;

    int gotInfo = getaddrinfo(EndpointIpOrName.c_str(), std::to_string(Port).c_str(), nullptr, &addresses);

    if (gotInfo != 0)
        throw GramException("Error getting address information -> " + std::string(gai_strerror(gotInfo)));
    
    struct addrinfo* target = addresses->ai_next;

    int connected = connect(socketFd, target->ai_addr, target->ai_addrlen);

    if (connected == -1)
        throw GramException("Error connecting to target -> " + std::string(strerror(errno)));

    Connected = true;
}

void TcpConnection::Close()
{
    if (socketFd == 0)
        return;        
    
    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing socket -> " + std::string(strerror(errno)));

    socketFd = 0;
    Connected = false;
}

void TcpConnection::Send(std::string message)
{
    if (message.empty())
        return;

    int sent = send(socketFd, message.c_str(), message.length(), 0);

    if (sent == -1)
        throw GramException("Error sending message -> " + std::string(strerror(errno)));
}