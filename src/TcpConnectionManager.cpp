#include "../include/TcpConnectionManager.hpp"

TcpConnectionManager::TcpConnectionManager()
{
}

TcpConnectionManager::~TcpConnectionManager()
{
    for(size_t i = 0; i < Connections.size(); i++)
        delete(Connections.at(i));
}

TcpConnection* TcpConnectionManager::CreateConnection()
{
    TcpConnection* connection = new TcpConnection();
    connection->EndpointIpOrName = nullptr;
    
    Connections.push_back(connection);

    return connection;
}

TcpConnection* TcpConnectionManager::CreateConnection(std::string endpointIpOrName, int port)
{
    TcpConnection* connection = new TcpConnection(endpointIpOrName, port);
    
    Connections.push_back(connection);

    return connection;
}

void TcpConnectionManager::OpenConnection(TcpConnection* connection)
{
    if (connection == nullptr)
        return;

    connection->Open();
}

void TcpConnectionManager::CloseConnection(TcpConnection* connection)
{
    if (connection == nullptr)
        return;

    connection->Close();
}

void TcpConnectionManager::CloseAllConnections()
{
    if (Connections.empty())
        return;

    for(size_t i = 0; i < Connections.size(); i++)
        Connections.at(i)->Close();    
}