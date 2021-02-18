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

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include "string.h"
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <vector>
#include <iostream>
#include <unistd.h>
#include <uuid/uuid.h>
#include <thread>

#include "../exceptions/GramException.hpp"

namespace gram
{
    class TcpServer
    {
    public:
        typedef void(*ReceivedHandler)(std::string);

        TcpServer();
        ~TcpServer();

        static const int STANDARD_PORT = 55556;
        static const int LISTEN_BACKLOG = 50;
        static const int BUFFER_SIZE = 4096;

        void Start();
        void Start(int bindPort);

        void Stop();

        template<typename Func, typename ...args>
        void AddReceivedHandler(Func handler)
        {
            if (handler == nullptr)
                return;

            receivedHandler = handler;
        }

        int GetListenerPort();
        std::string ServerId;

    private:
        int socketFd;
        struct sockaddr_in address;

        std::thread WaitThread;
        std::vector<std::thread> ConnectionThreads;

        void waitForConnections();
        void addConnection(int socketFd);

        ReceivedHandler receivedHandler;

        std::string createId();
    };
};

#endif