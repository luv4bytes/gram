#include "../../include/udp/UdpConnectionManager.hpp"

UdpConnectionManager::UdpConnectionManager()
{
}

UdpConnectionManager::~UdpConnectionManager()
{
}

UdpConnection* UdpConnectionManager::CreateConnection()
{
    UdpConnection* connection = new UdpConnection();

    return connection;
}

UdpConnection* UdpConnectionManager::CreateConnection(std::string endpointIpOrName, int port)
{
    UdpConnection* connection = new UdpConnection(endpointIpOrName, port);

    return connection;
}

void UdpConnectionManager::OpenConnection(UdpConnection* connection)
{
    if (connection == nullptr)
        return;

    connection->Open();
}

void UdpConnectionManager::CloseConnection(UdpConnection* connection)
{
    if (connection == nullptr)
        connection->Close();
}

void UdpConnectionManager::CloseAllConnections()
{
    if (Connections.empty())
        return;

    for(size_t i = 0; i < Connections.size(); i++)
        Connections.at(i)->Close();
}