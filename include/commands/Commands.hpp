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

#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include "string.h"

#include "../globals/Globals.hpp"

#include "../tcp/TcpServer.hpp"
#include "../tcp/TcpClient.hpp"

#include "../udp/UdpServer.hpp"

#include "../lua_api/LuaApi.hpp"

#include "Command.hpp"

namespace gram{

    class Commands
    {
    public:

        static const int COMMAND_SZ = 50;

        Commands();

        std::vector<Command> AvailableCommands;

        void WaitForCommand();

    private:

        /*
            TODO: 

            Clients:
            
            - Open and Close
            - Close all clients
            - Send

            - Tests

            Lua:
            
            - Define API
            - Implement API
        */

        void createCommands();
        void createExitCommand();
        void createQuitCommand();

        void createHelpCommand();

        /* SERVER */

        void createStartServerTcpCommand();
        void createStartServerUdpCommand();

        void createStopAllServersCommand();
        void createStopServerTcpCommand();
        void createStopServerUdpCommand();

        void createListServerCommand();

        void createListServerSettingsInfoCommand();
        void createListServerSettingsCommand();
        void createSetServerSettingCommand();

        void createPrintServerRingbufferCommand();
        void createPrintServerOutputFileCommand();

        /* CLIENTS */
        
        void createStartTcpClientCommand();

        void createListClientsCommand();

        void createOpenTcpClientCommand();
        void createCloseTcpClientCommand();

    };
};

#endif