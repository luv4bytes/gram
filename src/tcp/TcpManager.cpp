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

#include "../../include/tcp/TcpManager.hpp"

gram::TcpManager::~TcpManager()
{
    for(size_t i = 0; i < Servers.size(); i++)
        delete(Servers.at(i));

    for(size_t i = 0; i < Clients.size(); i++)
        delete(Clients.at(i));
}

void gram::TcpManager::AddServer(TcpServer* server)
{
    if (server == nullptr)
        return;

    Servers.push_back(server);
}

void gram::TcpManager::AddClient(TcpClient* client)
{
    if (client == nullptr)
        return;

    Clients.push_back(client);
}

void gram::TcpManager::StopAllServers()
{
    for(size_t i = 0; i < Servers.size(); i++)
        Servers.at(i)->Stop();
}

void gram::TcpManager::CloseAllClients()
{
    for(size_t i = 0; i < Clients.size(); i++)
        Clients.at(i)->CloseAllConnections();
}

void gram::TcpManager::PrintServers()
{
    for(size_t i = 0; i < Servers.size(); i++)
        std::cout << Servers.at(i)->ServerId << " - Port: " << Servers.at(i)->GetListenerPort() << std::endl;
}