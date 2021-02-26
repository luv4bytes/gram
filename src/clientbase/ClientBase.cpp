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

#include "../../include/clientbase/ClientBase.hpp"

gram::ClientBase::ClientBase()
{
    createId();
}

gram::ClientBase::ClientBase(std::string endpointIpOrName, int port)
{
    createId();

    EndpointIpOrName = endpointIpOrName;
    Port = port;
}

gram::ClientBase::~ClientBase()
{
}

void gram::ClientBase::Open()
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

void gram::ClientBase::Close()
{
    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing socket -> " + std::string(strerror(errno)));

    IsOpen = false;
}

void gram::ClientBase::SendText(std::string message)
{
    if (message.empty())
        return;

    int sent = send(socketFd, message.c_str(), message.length(), 0);

    if (sent == -1)
        throw GramException("Error sending message -> " + std::string(strerror(errno)));
}

void gram::ClientBase::SendFile(std::string filePath)
{
    if (filePath.empty())
        return;

    std::ifstream stream;
    stream.open(filePath);

    if (!stream.is_open())
        throw GramException("Error opening file to send");

    stream.seekg(0, std::ios::end);
    size_t len = stream.tellg();

    char buffer[len];
    memset(buffer, 0, len);

    stream.seekg(0, std::ios::beg);
    stream.read(buffer, len);
    stream.close();

    int sent = send(socketFd, buffer, len, 0);

    if (sent == -1)
        throw GramException("Error sending message -> " + std::string(strerror(errno)));
}

std::string gram::ClientBase::ClientTypeName()
{
    switch(Type)
    {
        case TCP:
            return "TCP";

        case UDP:
            return "UDP";
    }

    return "none";
}

void gram::ClientBase::createId()
{
    char str[UUID_STR_LEN];
    uuid_t uuid;

    uuid_generate(uuid);
    uuid_unparse(uuid, str);
    uuid_clear(uuid);

    std::string id("C" + std::string(str).substr(0, 3));

    ClientId = id;
}