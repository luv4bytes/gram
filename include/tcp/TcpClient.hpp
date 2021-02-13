#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <vector>
#include "TcpConnection.hpp"
#include "../GramException.hpp"

class TcpClient
{

private:

public:
    TcpClient();
    ~TcpClient();

    std::vector<TcpConnection*> Connections;

    TcpConnection* CreateConnection();
    TcpConnection* CreateConnection(std::string endpointIpOrName, int port);

    void OpenConnection(TcpConnection* connection);
    void CloseConnection(TcpConnection* connection);
    void CloseAllConnections();
};

#endif