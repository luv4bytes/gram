#include "../../include/tcp/TcpServer.hpp"

TcpServer::TcpServer()
{
}

TcpServer::~TcpServer()
{
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
}

void TcpServer::Stop()
{
    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing server socket -> " + std::string(strerror(errno)));

    socketFd = 0;
}