#include "../../include/tcp/TcpClient.hpp"

TcpClient::TcpClient()
{
}

TcpClient::~TcpClient()
{
    for(size_t i = 0; i < Connections.size(); i++)
        delete(Connections.at(i));
}

TcpConnection* TcpClient::CreateConnection()
{
    TcpConnection* connection = new TcpConnection();
    connection->EndpointIpOrName = nullptr;
    
    Connections.push_back(connection);

    return connection;
}

TcpConnection* TcpClient::CreateConnection(std::string endpointIpOrName, int port)
{
    TcpConnection* connection = new TcpConnection(endpointIpOrName, port);
    
    Connections.push_back(connection);

    return connection;
}

void TcpClient::OpenConnection(TcpConnection* connection)
{
    if (connection == nullptr)
        return;

    connection->Open();
}

void TcpClient::CloseConnection(TcpConnection* connection)
{
    if (connection == nullptr)
        return;

    connection->Close();
}

void TcpClient::CloseAllConnections()
{
    if (Connections.empty())
        return;

    for(size_t i = 0; i < Connections.size(); i++)
        Connections.at(i)->Close();    
}