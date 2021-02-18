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

#include "../../include/commands/Commands.hpp"

gram::Commands::Commands()
{
    createCommands();
}

void gram::Commands::createCommands()
{
    createExitCommand();
    createQuitCommand();

    createStartServerTcpCommand();
    createStartServerUdpCommand();

    createStopServerTcpCommand();
    createStopServerUdpCommand();

    createListServersCommand();
    createListTcpServersCommand();
    createListUdpServersCommand();
}

void gram::Commands::createExitCommand()
{
    Command cmdExit;
    cmdExit.CommandName = "exit";
    cmdExit.Description = "Quits the program";

    cmdExit.AssignHandler([](){
        exit(0);
    });

    AvailableCommands.push_back(cmdExit);
}

void gram::Commands::createQuitCommand()
{
    Command quit;
    quit.CommandName = "quit";
    quit.Description = "Quits the program";

    quit.AssignHandler([](){
        exit(0);
    });

    AvailableCommands.push_back(quit);
}

void gram::Commands::createStartServerTcpCommand()
{
    Command tcpServer;
    tcpServer.CommandName = "start server tcp";
    tcpServer.Description = "Starts a TCP server on the given port";

    tcpServer.AssignHandler([](){

        int port = 0;

        std::cout << "Port (0 for std port): ";

        if (!(std::cin >> port))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            throw GramException("Error setting port");
        }

        TcpServer* server = new TcpServer();

        // TODO: message handler

        if (port != 0)
            server->Start(port);
        else
            server->Start();

        GlobalTcpManager.AddServer(server);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    });

    AvailableCommands.push_back(tcpServer);
}

void gram::Commands::createStartServerUdpCommand()
{
    Command udpServer;
    udpServer.CommandName = "start server udp";
    udpServer.Description = "Starts a UDP server on the given port";

    udpServer.AssignHandler([](){

        int port = 0;

        std::cout << "Port (0 for std port): ";

        if (!(std::cin >> port))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            throw GramException("Error setting port");
        }  

        UdpServer* server = new UdpServer();
        
        // TODO: message handler

        if (port != 0)
            server->Start(port);
        else
            server->Start();

        GlobalUdpManager.AddServer(server);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    });

    AvailableCommands.push_back(udpServer);
}

void gram::Commands::createStopServerTcpCommand()
{
    Command stopServerTcp;
    stopServerTcp.CommandName = "stop server tcp";
    stopServerTcp.Description = "Stops a TCP server with given id";

    stopServerTcp.AssignHandler([](){

        std::string serverId;

        std::cout << "Server Id: ";

        if (!(std::cin >> serverId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            throw GramException("Error setting server id");
        }

        TcpServer* server = GlobalTcpManager.WhereServer([=](TcpServer* server){
            return (server->ServerId.compare(serverId) == 0);
        });

        if (server == nullptr)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        server->Stop();
        GlobalTcpManager.RemoveServer(server);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    });

    AvailableCommands.push_back(stopServerTcp);
}

void gram::Commands::createStopServerUdpCommand()
{
    Command stopServerUdp;
    stopServerUdp.CommandName = "stop server udp";
    stopServerUdp.Description = "Stops a UDP server with given id";

    stopServerUdp.AssignHandler([](){

        std::string serverId;

        std::cout << "Server Id: ";

        if (!(std::cin >> serverId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            throw GramException("Error setting server id");
        }

        UdpServer* server = GlobalUdpManager.WhereServer([=](UdpServer* server){
            return (server->ServerId.compare(serverId) == 0);
        });

        if (server == nullptr)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        server->Stop();
        GlobalUdpManager.RemoveServer(server);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    });

    AvailableCommands.push_back(stopServerUdp);
}

void gram::Commands::createListServersCommand()
{
    Command listServers;
    listServers.CommandName = "list servers";
    listServers.Description = "Prints out a list of all servers";

    listServers.AssignHandler([](){

        GlobalTcpManager.PrintServers();
        GlobalUdpManager.PrintServers();            

    });

    AvailableCommands.push_back(listServers);
}

void gram::Commands::createListTcpServersCommand()
{
    Command listTcpServers;
    listTcpServers.CommandName = "list servers tcp";
    listTcpServers.Description = "Prints out a list of current TCP servers";
    
    listTcpServers.AssignHandler([](){

        GlobalTcpManager.PrintServers();

    });

    AvailableCommands.push_back(listTcpServers);
}

void gram::Commands::createListUdpServersCommand()
{
    Command listUdpServers;
    listUdpServers.CommandName = "list servers udp";
    listUdpServers.Description = "Prints out a list of current UDP servers";
    
    listUdpServers.AssignHandler([](){

        GlobalUdpManager.PrintServers();

    });

    AvailableCommands.push_back(listUdpServers);
}

static inline void trim(std::string& s)
{
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
}

static inline void tolower(std::string& s)
{
    for(size_t i = 0; i < s.size(); i++)
        s[i] = std::tolower(s[i]);
}

void gram::Commands::WaitForCommand()
{
    char input[COMMAND_SZ];
    memset(input, 0, COMMAND_SZ);

    std::cout << "> ";
    if (!std::cin.getline(input, COMMAND_SZ))
        throw GramException("Error getting input");

    if (input[0] == '\0')
        return;  

    std::string command(input);
    trim(command);
    tolower(command);

    for(size_t i = 0; i < AvailableCommands.size(); i++)
    {
        if (AvailableCommands.at(i).Found(command))
        {
            AvailableCommands.at(i).Execute();
            break;
        }
    }
}