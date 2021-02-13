#ifndef TCPCONNECTIONMANAGER_H
#define TCPCONNECTIONMANAGER_H

#include <vector>
#include "TcpConnection.hpp"
#include "../GramException.hpp"

class TcpConnectionManager
{

private:

public:
    TcpConnectionManager();
    ~TcpConnectionManager();

    std::vector<TcpConnection*> Connections;

    TcpConnection* CreateConnection();
    TcpConnection* CreateConnection(std::string endpointIpOrName, int port);

    void OpenConnection(TcpConnection* connection);
    void CloseConnection(TcpConnection* connection);
    void CloseAllConnections();
};

#endif