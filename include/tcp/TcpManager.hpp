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

#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include "TcpClient.hpp"
#include "TcpServer.hpp"

#include <iostream>
#include <vector>

namespace gram
{
    class TcpManager
    {
    public:

        ~TcpManager();

        std::vector<TcpServer*> Servers;
        std::vector<TcpClient*> Clients;

        void AddServer(TcpServer* server);
        void AddClient(TcpClient* client);

        void StopAllServers();
        void CloseAllClients();

        void PrintServers();

        template <typename F>
        TcpServer* WhereServer(F predicate)
        {
            for(size_t i = 0; i < Servers.size(); i++)
                if (predicate(Servers.at(i)))
                    return Servers.at(i);

            return nullptr;
        }

        void RemoveServer(TcpServer* server);
    };
}

#endif