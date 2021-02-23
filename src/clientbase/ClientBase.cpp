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
}

gram::ClientBase::ClientBase(std::string endpointIpOrName, int port)
{
    EndpointIpOrName = endpointIpOrName;
    Port = port;
}

gram::ClientBase::~ClientBase()
{
}

void gram::ClientBase::Open()
{
}

void gram::ClientBase::Close()
{
}

void gram::ClientBase::Send(std::string message)
{
    if (message.empty())
        return;

    int sent = send(socketFd, message.c_str(), message.length(), 0);

    if (sent == -1)
        throw GramException("Error sending message -> " + std::string(strerror(errno)));
}