#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include "string.h"
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "../GramException.hpp"

class TcpServer
{

private:
    int socketFd;
    struct sockaddr_in address;

public:
    TcpServer();
    ~TcpServer();

    static const int STANDARD_PORT = 55556;
    static const int LISTEN_BACKLOG = 50;

    void Start();
    void Start(int bindPort);

    void Stop();
};

#endif