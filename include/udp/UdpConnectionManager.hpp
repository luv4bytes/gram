#ifndef UDPCONNECTIONMANAGER_H
#define UDPCONNECTIONMANAGER_H

#include <string>
#include <vector>

#include "UdpConnection.hpp"
#include "../GramException.hpp"

class UdpConnectionManager
{

private:

public:
    UdpConnectionManager();
    ~UdpConnectionManager();

    std::vector<UdpConnection*> Connections;

    UdpConnection* CreateConnection();
    UdpConnection* CreateConnection(std::string endpointIpOrName, int port);

    void OpenConnection(UdpConnection* connection);
    void CloseConnection(UdpConnection* connection);
    void CloseAllConnections();
};

#endif