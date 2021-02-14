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