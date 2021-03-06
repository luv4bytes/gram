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

#include "../../include/tcp/TcpSslClient.hpp"

gram::TcpSslClient::TcpSslClient()
{
    Type = TCP;
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));
}

gram::TcpSslClient::TcpSslClient(std::string endpointIpOrName, int port)
{
    Type = TCP;    
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    EndpointIpOrName = endpointIpOrName;
    Port = port;
}

gram::TcpSslClient::~TcpSslClient()
{
}

void gram::TcpSslClient::Open()
{
    struct addrinfo* addresses;

    int gotInfo = getaddrinfo(EndpointIpOrName.c_str(), std::to_string(Port).c_str(), nullptr, &addresses);

    if (gotInfo != 0)
        throw GramException("Error getting address information -> " + std::string(gai_strerror(gotInfo)));
    
    struct addrinfo* target = addresses->ai_next;

    int connected = connect(socketFd, target->ai_addr, target->ai_addrlen);

    if (connected == -1)
        throw GramException("Error connecting to target -> " + std::string(strerror(errno)));

    const SSL_METHOD* method = TLS_client_method();
    SslContext = SSL_CTX_new(method);
    Ssl = SSL_new(SslContext);
    
    SSL_set_fd(Ssl, socketFd);

    int sslConnect = SSL_connect(Ssl);

    if (sslConnect == -1)
        throw GramException(ERR_lib_error_string(ERR_get_error()));

    IsOpen = true;
}

void gram::TcpSslClient::Close()
{
    SSL_shutdown(Ssl);

    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing socket -> " + std::string(strerror(errno)));

    if (Ssl != NULL)
        SSL_free(Ssl);

    if (IsOpen)
        if (SslContext != NULL)
            SSL_CTX_free(SslContext);

    IsOpen = false;
}

void gram::TcpSslClient::SendText(std::string message)
{
    // TODO:
}

void gram::TcpSslClient::SendFile(std::string filePath)
{
    // TODO:
}

static inline void trim(std::string& s)
{
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
}

gram::TcpSslClient* gram::TcpSslClient::PromptAndCreateClient()
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

    TcpSslClient* client = new TcpSslClient(endpoint, port);

    std::cout << "Created client " + client->ClientId << std::endl;

    return client;
}