/* Copyright (c) 2021 Lukas Pfeifer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "../../include/udp/UdpClient.hpp"

gram::UdpClient::UdpClient()
{
}

gram::UdpClient::~UdpClient()
{
}

gram::UdpConnection* gram::UdpClient::CreateConnection()
{
    UdpConnection* connection = new UdpConnection();

    return connection;
}

gram::UdpConnection* gram::UdpClient::CreateConnection(std::string endpointIpOrName, int port)
{
    UdpConnection* connection = new UdpConnection(endpointIpOrName, port);

    return connection;
}

void gram::UdpClient::OpenConnection(UdpConnection* connection)
{
    if (connection == nullptr)
        return;

    connection->Open();
}

void gram::UdpClient::CloseConnection(UdpConnection* connection)
{
    if (connection == nullptr)
        connection->Close();
}

void gram::UdpClient::CloseAllConnections()
{
    if (Connections.empty())
        return;

    for(size_t i = 0; i < Connections.size(); i++)
        Connections.at(i)->Close();
}