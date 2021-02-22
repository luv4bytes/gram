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

#include "../../include/serverbase/ServerBaseManager.hpp"

gram::ServerBaseManager::~ServerBaseManager()
{
    for(size_t i = 0; i < Servers.size(); i++)
        delete(Servers.at(i));
}

void gram::ServerBaseManager::AddServer(ServerBase* server)
{
    if (server == nullptr)
        return;

    Servers.push_back(server);
}

void gram::ServerBaseManager::StopAllServers()
{
    for(size_t i = 0; i < Servers.size(); i++)
        Servers.at(i)->Stop();

    for(size_t i = 0; i < Servers.size(); i++)
        delete(Servers.at(i));

    Servers.clear();
}

void gram::ServerBaseManager::PrintServers()
{
    for(size_t i = 0; i < Servers.size(); i++)
        std::cout << Servers.at(i)->ServerId << " - Port: " << Servers.at(i)->Port << " - Name: " << Servers.at(i)->ServerName << std::endl;
}

void gram::ServerBaseManager::RemoveServer(ServerBase* server)
{
    if (server == nullptr)
        return;

    for(size_t i = 0; i < Servers.size(); i++)
    {
        if (Servers.at(i)->ServerId.compare(server->ServerId) == 0)
        {
            Servers.erase(Servers.begin() + i);
            break;
        }
    }

    delete(server);
}

void gram::ServerBaseManager::CleanUp()
{
    StopAllServers();
}