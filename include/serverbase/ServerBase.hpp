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

#ifndef SERVERBASE_H
#define SERVERBASE_H

#include "uuid/uuid.h"
#include <fstream>
#include <string.h>

#include "../settings/ServerSettings.hpp"

namespace gram
{
    class ServerBase
    {
    public:
        ServerBase();
        ~ServerBase();

        enum ServerType
        {
            TCP,
            UDP
        };

        ServerType Type;

        ServerSettings Settings;

        static const int SELECT_TIMEOUT_MICROSECONDS = 500000;
        static const int NAME_LENGTH = 50;
        static const int RINGBUFFER_LENGTH = 128000;

        std::string ServerId;
        std::string ServerName;
        int Port;

        char RingBuffer[RINGBUFFER_LENGTH];
        char* RingBufferCurrent;
        char* RingBufferEnd;

        virtual void Start();
        virtual void Stop();

        void PromptAndSetSetting(int settingId);

        void writeMessageToFile(std::string message);
        void writeMessageToRingbuffer(std::string message);

        std::string ServerTypeName();

    private:
        void createId();

        void clearRingBuffer();
        
        virtual void received(std::string message);
    };
}

#endif