#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <string>
#include "string.h"
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "GramException.hpp"

class TcpConnection
{

private:

    int socketFd;

public:
    TcpConnection();
    TcpConnection(std::string endpointIpOrName, int port);
    ~TcpConnection();

    std::string EndpointIpOrName;
    int Port;

    void Open();
    void Close();

    void Send(std::string message);
};

#endif