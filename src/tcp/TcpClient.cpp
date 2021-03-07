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
    Type = TCP;    
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));
}

gram::TcpClient::TcpClient(std::string endpointIpOrName, int port)
{
    Type = TCP;
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    EndpointIpOrName = endpointIpOrName;
    Port = port;
}

gram::TcpClient::~TcpClient()
{
}

static inline void trim(std::string& s)
{
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
}

std::shared_ptr<gram::TcpClient> gram::TcpClient::PromptAndCreateClient()
{
    int bufsz = 150;
    char bufP[bufsz];
    memset(bufP, 0, bufsz);
    int port;
    std::string endpoint;

    std::cout << "[server]:[port]: ";
    if (!(std::cin.getline(bufP, bufsz)))
        throw GramException("Please specify endpoint and port");

    std::string bufS(bufP);
    size_t pos = bufS.find(':');

    endpoint = bufS.substr(0, pos);
    trim(endpoint);

    port = atoi(bufS.substr(pos + 1, bufS.size()).c_str());

    std::shared_ptr<TcpClient> client = std::shared_ptr<TcpClient>(new TcpClient(endpoint, port));

    std::cout << "Created client " + client->ClientId << std::endl;

    return client;
}