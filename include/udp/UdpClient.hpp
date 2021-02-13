#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <string>
#include <vector>

#include "UdpConnection.hpp"
#include "../GramException.hpp"

class UdpClient
{

private:

public:
    UdpClient();
    ~UdpClient();

    std::vector<UdpConnection*> Connections;

    UdpConnection* CreateConnection();
    UdpConnection* CreateConnection(std::string endpointIpOrName, int port);

    void OpenConnection(UdpConnection* connection);
    void CloseConnection(UdpConnection* connection);
    void CloseAllConnections();
};

#endif