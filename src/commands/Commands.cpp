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

    createHelpCommand();

    createStartServerTcpCommand();
    createStartServerUdpCommand();

    createStopAllServersCommand();
    createStopServerTcpCommand();
    createStopServerUdpCommand();

    createListServerCommand();
    
    createListServerSettingsInfoCommand();
    createListServerSettingsCommand();
    createSetServerSettingCommand();

    createPrintServerRingbufferCommand();
    createPrintServerOutputFileCommand();

    createStartTcpClientCommand();
    createStartUdpClientCommand();

    createListClientsCommand();
    
    createOpenClientCommand();
    createCloseClientCommand();

    createClientSendFileCommand();
    createClientSendTextCommand();

    createCloseAllClientsCommand();
}

void gram::Commands::createExitCommand()
{
    Command cmdExit;
    cmdExit.CommandName = "exit";
    cmdExit.Description = "Quits the program";

    cmdExit.AssignHandler([](){

        GlobalServerManager.CleanUp();
        GlobalClientManager.CleanUp();

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

        GlobalServerManager.CleanUp();
        GlobalClientManager.CleanUp();

        exit(0);
    });

    AvailableCommands.push_back(quit);
}

void gram::Commands::createHelpCommand()
{
    Command help;
    help.CommandName = "help";
    help.Description = "Prints information about commands";

    help.AssignHandler([](){
        
        const char* format = "   %-25s|  %-15s|  %-30s\n";

        printf("Following commands can be used to control gram:\n\n");
        printf(format, "Long command", "Short command", "Description");
        printf("--------------------------------------------------------------\n");

        for(size_t i = 0; i < GlobalCommandsPtr->AvailableCommands.size(); i++)
            printf(format, GlobalCommandsPtr->AvailableCommands.at(i).CommandName.c_str(),
                           GlobalCommandsPtr->AvailableCommands.at(i).ShortCommand.c_str(),
                           GlobalCommandsPtr->AvailableCommands.at(i).Description.c_str());

        printf("\n\ngram is licensed under MIT License\n");
        printf("Lukas Pfeifer - https://github.com/luv4bytes\n");
    });

    AvailableCommands.push_back(help);
}

void gram::Commands::createStartServerTcpCommand()
{
    Command tcpServer;
    tcpServer.CommandName = "start server tcp";
    tcpServer.ShortCommand = "stcp";
    tcpServer.Description = "Starts a TCP server on the given port";

    tcpServer.AssignHandler([](){

        TcpServer* newServer = TcpServer::PromptAndCreateNewServer();
        newServer->Start();

        GlobalServerManager.AddServer(newServer);
    });

    AvailableCommands.push_back(tcpServer);
}

void gram::Commands::createStartServerUdpCommand()
{
    Command udpServer;
    udpServer.CommandName = "start server udp";
    udpServer.ShortCommand = "sudp";
    udpServer.Description = "Starts a UDP server on the given port";

    udpServer.AssignHandler([](){

        UdpServer* newServer = UdpServer::PromptAndCreateNewServer();
        newServer->Start();

        GlobalServerManager.AddServer(newServer);        
    });

    AvailableCommands.push_back(udpServer);
}

void gram::Commands::createStopAllServersCommand()
{
    Command stopAllServers;
    stopAllServers.CommandName = "stop server all";
    stopAllServers.ShortCommand = "ssa";
    stopAllServers.Description = "Stops all running servers";

    stopAllServers.AssignHandler([](){

        GlobalServerManager.StopAllServers();
    });

    AvailableCommands.push_back(stopAllServers);
}

void gram::Commands::createStopServerTcpCommand()
{
    Command stopServerTcp;
    stopServerTcp.CommandName = "stop server tcp";
    stopServerTcp.ShortCommand = "sstcp";
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

        ServerBase* server = GlobalServerManager.WhereServer([=](ServerBase* server){
            return ((server->ServerId.compare(serverId) == 0) && (server->Type == ServerBase::TCP));
        });

        if (server == nullptr)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        server->Stop();
        GlobalServerManager.RemoveServer(server);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    });

    AvailableCommands.push_back(stopServerTcp);
}

void gram::Commands::createStopServerUdpCommand()
{
    Command stopServerUdp;
    stopServerUdp.CommandName = "stop server udp";
    stopServerUdp.ShortCommand = "ssudp";
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

        ServerBase* server = GlobalServerManager.WhereServer([=](ServerBase* server){
            return ((server->ServerId.compare(serverId) == 0) && (server->Type == ServerBase::UDP));
        });

        if (server == nullptr)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        server->Stop();
        GlobalServerManager.RemoveServer(server);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    });

    AvailableCommands.push_back(stopServerUdp);
}

void gram::Commands::createListServerCommand()
{
    Command listServers;
    listServers.CommandName = "list server";
    listServers.ShortCommand = "lsrv";
    listServers.Description = "Prints out a list of all servers";

    listServers.AssignHandler([](){

        GlobalServerManager.PrintServers();

    });

    AvailableCommands.push_back(listServers);
}

void gram::Commands::createListServerSettingsInfoCommand()
{
    Command listServerSettingsInfo;
    listServerSettingsInfo.CommandName = "server settings info";
    listServerSettingsInfo.ShortCommand = "sseti";
    listServerSettingsInfo.Description = "Prints available settings to set for servers";

    listServerSettingsInfo.AssignHandler([](){
        GlobalSettingsInfo.PrintServerSettingsInfo();
    });

    AvailableCommands.push_back(listServerSettingsInfo);
}

void gram::Commands::createListServerSettingsCommand()
{
    Command listServerSettings;
    listServerSettings.CommandName = "server settings";
    listServerSettings.ShortCommand = "sset";
    listServerSettings.Description = "Prints out current settings for a given server";

    listServerSettings.AssignHandler([](){

        std::string serverId;
        std::cout << "Server Id: ";

        if (!(std::cin >> serverId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            throw GramException("Server id not valid");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        ServerBase* server = GlobalServerManager.WhereServer([=](ServerBase* server){
            return server->ServerId.compare(serverId) == 0;
        });

        if (server == nullptr)
            return;
        
        server->Settings.PrintServerSettings();
    });

    AvailableCommands.push_back(listServerSettings);
}

void gram::Commands::createSetServerSettingCommand()
{
    Command setServerSetting;
    setServerSetting.CommandName = "set server setting";
    setServerSetting.ShortCommand = "ssets";
    setServerSetting.Description = "Prompts the user to enter settings for a server";

    setServerSetting.AssignHandler([](){
        std::string serverId;
        int settingsId = 0;

        std::cout << "Server Id: ";
        if (!(std::cin >> serverId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            throw GramException("Server id not valid");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Settings Id: ";
        if (!(std::cin >> settingsId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            throw GramException("Settings id not valid");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        ServerBase* server = GlobalServerManager.WhereServer([=](ServerBase* server){
            return server->ServerId.compare(serverId) == 0;
        });

        if (server == nullptr)
            return;

        server->PromptAndSetSetting(settingsId);
    });

    AvailableCommands.push_back(setServerSetting);
}

void gram::Commands::createPrintServerRingbufferCommand()
{
    Command printRingbuffer;
    printRingbuffer.CommandName = "print server ringbuffer";
    printRingbuffer.ShortCommand = "psrb";
    printRingbuffer.Description = "Prints the ringbuffer of the given server";

    printRingbuffer.AssignHandler([](){

        std::string serverId;

        std::cout << "Server Id: ";
        if (!(std::cin >> serverId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            throw GramException("Server id not valid");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        ServerBase* server = GlobalServerManager.WhereServer([=](ServerBase* server){
            return (server->ServerId.compare(serverId) == 0);
        });
        
        if (server == nullptr)
            return;

        server->PrintRingbuffer();
    });

    AvailableCommands.push_back(printRingbuffer);
}

void gram::Commands::createPrintServerOutputFileCommand()
{
    Command printOutputFile;
    printOutputFile.CommandName = "print server output file";
    printOutputFile.Description = "Prints the contents of the specified output file for the server";
    printOutputFile.ShortCommand = "psof";

    printOutputFile.AssignHandler([](){

        std::string serverId;

        std::cout << "Server Id: ";
        if (!(std::cin >> serverId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            throw GramException("Server id not valid");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        ServerBase* server = GlobalServerManager.WhereServer([=](ServerBase* server){
            return (server->ServerId.compare(serverId) == 0);
        });

        if (server == nullptr)
            return;

        server->PrintOutputFile();
    });

    AvailableCommands.push_back(printOutputFile);
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

void gram::Commands::createStartTcpClientCommand()
{
    Command startTcpClient;
    startTcpClient.CommandName = "start client tcp";
    startTcpClient.ShortCommand = "ctcp";
    startTcpClient.Description = "Start a new TCP client";

    startTcpClient.AssignHandler([](){
        
        TcpClient* client = TcpClient::PromptAndCreateClient();

        GlobalClientManager.AddClient(client);
    });

    AvailableCommands.push_back(startTcpClient);
}

void gram::Commands::createStartUdpClientCommand()
{
    Command startUdpClient;
    startUdpClient.CommandName = "start client udp";
    startUdpClient.ShortCommand = "cudp";
    startUdpClient.Description = "Start a new UDP client";

    startUdpClient.AssignHandler([](){

        UdpClient* client = UdpClient::PromptAndCreateClient();

        GlobalClientManager.AddClient(client);
    });

    AvailableCommands.push_back(startUdpClient);
}

void gram::Commands::createListClientsCommand()
{
    Command listClients;
    listClients.CommandName = "list clients";
    listClients.ShortCommand = "lcl";
    listClients.Description = "Prints out a list of all clients";

    listClients.AssignHandler([](){

        GlobalClientManager.PrintClients();
    });

    AvailableCommands.push_back(listClients);
}

void gram::Commands::createOpenClientCommand()
{
    Command openClient;
    openClient.CommandName = "open client";
    openClient.ShortCommand = "oc";
    openClient.Description = "Opens the connection to specified endpoint";

    openClient.AssignHandler([](){

        std::string clientId;

        std::cout << "Client Id: ";
        if (!(std::cin >> clientId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            throw GramException("Client id not valid");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        ClientBase* client = GlobalClientManager.WhereClient([=](ClientBase* client){
            return (client->ClientId.compare(clientId) == 0);
        });

        if (client == nullptr)
            return;

        client->Open();
    });

    AvailableCommands.push_back(openClient);
}

void gram::Commands::createCloseClientCommand()
{
    Command closeTcpClient;
    closeTcpClient.CommandName = "close client";
    closeTcpClient.ShortCommand = "cc";
    closeTcpClient.Description = "Closes the specified client";

    closeTcpClient.AssignHandler([](){

        std::string clientId;

        std::cout << "Client Id: ";

        if (!(std::cin >> clientId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            throw GramException("Error setting client id");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        ClientBase* client = GlobalClientManager.WhereClient([=](ClientBase* client){
            return (client->ClientId.compare(clientId) == 0);
        });

        if (client == nullptr)
            return;

        client->Close();
        GlobalClientManager.RemoveClient(client);
    });

    AvailableCommands.push_back(closeTcpClient);
}

void gram::Commands::createClientSendFileCommand()
{
    Command sendFile;
    sendFile.CommandName = "client send file";
    sendFile.ShortCommand = "csf";
    sendFile.Description = "Send a given file to the endpoint";

    sendFile.AssignHandler([](){

        std::string clientId;
        std::string filePath;

        std::cout << "Client Id: ";

        if (!(std::cin >> clientId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            throw GramException("Error setting client id");
        }

        std::cout << "File path: ";

        if (!(std::cin >> filePath))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            throw GramException("Error setting file path");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        ClientBase* client = GlobalClientManager.WhereClient([=](ClientBase* client){
                return (client->ClientId.compare(clientId) == 0);
        });

        if (client == nullptr)
            return;

        client->SendFile(filePath);
    });
    
    AvailableCommands.push_back(sendFile);
}

void gram::Commands::createClientSendTextCommand()
{
    Command sendText;
    sendText.CommandName = "client send text";
    sendText.ShortCommand = "cst";
    sendText.Description = "Send a given text to the endpoint";

    sendText.AssignHandler([](){

        std::string clientId;
        char buffer[ClientBase::MSG_BUFFER_SIZE];
        memset(buffer, 0, ClientBase::MSG_BUFFER_SIZE);

        std::cout << "Client Id: ";

        if (!(std::cin >> clientId))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            throw GramException("Error setting client id");
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter text: ";

        if (!(std::cin.getline(buffer, ClientBase::MSG_BUFFER_SIZE)))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            throw GramException("Error setting text");
        }

        ClientBase* client = GlobalClientManager.WhereClient([=](ClientBase* client){
                return (client->ClientId.compare(clientId) == 0);
        });

        if (client == nullptr)
            return;

        client->SendText(std::string(buffer));
    });
    
    AvailableCommands.push_back(sendText);
}

void gram::Commands::createCloseAllClientsCommand()
{
    Command closeAllClients;
    closeAllClients.CommandName = "close all clients";
    closeAllClients.ShortCommand = "cac";
    closeAllClients.Description = "Closes all clients";

    closeAllClients.AssignHandler([](){

        GlobalClientManager.CloseAllClients();
    });

    AvailableCommands.push_back(closeAllClients);
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