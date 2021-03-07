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

#ifndef SERVERBASEMANAGER_H
#define SERVERBASEMANAGER_H

#include "ServerBase.hpp"

#include <memory>

namespace gram
{
    class ServerBaseManager
    {
    public:

        ~ServerBaseManager();

        std::vector<std::shared_ptr<ServerBase>> Servers;

        void AddServer(std::shared_ptr<ServerBase> server);

        void StopAllServers();

        void PrintServers();

        template <typename F>
        std::shared_ptr<ServerBase> WhereServer(F predicate)
        {
            for(size_t i = 0; i < Servers.size(); i++)
                if (predicate(Servers.at(i)))
                    return Servers.at(i);

            return nullptr;
        }

        void RemoveServer(std::shared_ptr<ServerBase> server);

        void CleanUp();
    };
}

#endif