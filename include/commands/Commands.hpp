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

#include "../tcp/TcpClient.hpp"
#include "../tcp/TcpServer.hpp"

#include "../udp/UdpClient.hpp"
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

            Server:

            - Server settings
            - Message handling

            Clients:
            
            - Create clients
            - List clients
            - Close clients
            - Close single client
        */

        void createCommands();
        void createExitCommand();
        void createQuitCommand();
        
        void createStartServerTcpCommand();
        void createStartServerUdpCommand();

        void createStopAllServersCommand();
        void createStopServerTcpCommand();
        void createStopServerUdpCommand();

        void createListServerCommand();

        void createStartTcpClientCommand();
        void createStartUdpClientCommand();

        void createListServerSettingsInfoCommand();
        void createSetServerSettingCommand();

        void createHelpCommand();
    };
};

#endif