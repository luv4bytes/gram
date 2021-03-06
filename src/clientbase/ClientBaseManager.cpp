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

#include "../../include/clientbase/ClientBaseManager.hpp"

void gram::ClientBaseManager::AddClient(std::shared_ptr<ClientBase> client)
{
    if (client == nullptr)
        return;

    Clients.push_back(client);
}

void gram::ClientBaseManager::CloseAllClients()
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        Clients.at(i)->Close();
        std::cout << "Closed client " << Clients.at(i)->ClientId << std::endl;
    }

    Clients.clear();
}

void gram::ClientBaseManager::PrintClients()
{
    for(size_t i = 0; i < Clients.size(); i++)
    {
        std::shared_ptr<ClientBase> client = Clients.at(i);
        std::cout << client->ClientId << " (" << client->ClientTypeName() << ") - Port: " << client->Port << std::endl;
    }
}

void gram::ClientBaseManager::RemoveClient(std::shared_ptr<ClientBase> client)
{
    if (client == nullptr)
        return;

    for(size_t i = 0; i < Clients.size(); i++)
    {
        if (Clients.at(i)->ClientId.compare(client->ClientId) == 0)
        {
            Clients.erase(Clients.begin() + i);
            break;
        }
    }
}

void gram::ClientBaseManager::CleanUp()
{
    CloseAllClients();
}