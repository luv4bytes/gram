#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <string>
#include "string.h"
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "../exceptions/GramException.hpp"

class UdpConnection
{
private:
    
    int socketFd;

public:
    UdpConnection();
    UdpConnection(std::string endpointIpOrName, int port);
    ~UdpConnection();

    std::string EndpointIpOrName;
    int Port;

    void Open();
    void Close();

    void Send(std::string message);
};

#endif