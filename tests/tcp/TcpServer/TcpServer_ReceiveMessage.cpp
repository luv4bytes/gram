#include "../../../include/tcp/TcpServer.hpp"
#include "../../../include/tcp/TcpClient.hpp"

#include <iostream>

bool breakRcv = false;

int main()
{
    TcpServer server;

    server.AddReceivedHandler([](std::string msg){
        breakRcv = true;
    });

    server.Start();

    TcpClient client;
    auto connection = client.CreateConnection("127.0.0.1", TcpServer::STANDARD_PORT);
    connection->Open();
    connection->Send("Hello");

    while(!breakRcv){}

    return 0;
}