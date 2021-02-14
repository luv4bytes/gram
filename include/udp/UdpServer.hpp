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

#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <string>
#include "string.h"
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <thread>

#include "../exceptions/GramException.hpp"

class UdpServer
{
public:
    typedef void(*ReceivedHandler)(std::string);

    UdpServer();
    ~UdpServer();

    static const int STANDARD_PORT = 55557;
    static const int BUFFER_SIZE = 65535;

    void Start();
    void Start(int bindPort);

    void Stop();

    template<typename T>
    void AddReceivedHandler(T handler)
    {
        if (handler == nullptr)
            return;

        receivedHandler = handler;
    }

private:
    int socketFd;
    struct sockaddr_in address;

    std::thread WaitThread;
    std::vector<std::thread> ConnectionThreads;

    void waitForDatagrams();

    ReceivedHandler receivedHandler;
};

#endif