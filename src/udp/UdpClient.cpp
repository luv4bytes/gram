#include "../../include/udp/UdpClient.hpp"

UdpClient::UdpClient()
{
}

UdpClient::~UdpClient()
{
}

UdpConnection* UdpClient::CreateConnection()
{
    UdpConnection* connection = new UdpConnection();

    return connection;
}

UdpConnection* UdpClient::CreateConnection(std::string endpointIpOrName, int port)
{
    UdpConnection* connection = new UdpConnection(endpointIpOrName, port);

    return connection;
}

void UdpClient::OpenConnection(UdpConnection* connection)
{
    if (connection == nullptr)
        return;

    connection->Open();
}

void UdpClient::CloseConnection(UdpConnection* connection)
{
    if (connection == nullptr)
        connection->Close();
}

void UdpClient::CloseAllConnections()
{
    if (Connections.empty())
        return;

    for(size_t i = 0; i < Connections.size(); i++)
        Connections.at(i)->Close();
}