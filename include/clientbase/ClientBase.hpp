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

#ifndef CLIENTBASE_HPP
#define CLIENTBASE_HPP

#include <string>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "string.h"
#include "uuid/uuid.h"
#include "../exceptions/GramException.hpp"

namespace gram
{
    class ClientBase
    {
    protected:
        int socketFd;

    public:
        ClientBase();
        ClientBase(std::string endpointIpOrName, int port);

        ~ClientBase();

        enum ClientType
        {
            TCP,
            UDP
        };

        static const int MSG_BUFFER_SIZE = 65535;

        bool IsOpen;

        std::string ClientId;
        std::string EndpointIpOrName;
        int Port;
        ClientType Type;

        virtual void Open();
        virtual void Close();

        void SendText(std::string message);
        void SendFile(std::string filePath);

        std::string ClientTypeName();

    private:
        void createId();
    };
};

#endif