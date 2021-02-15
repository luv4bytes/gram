#include "../../../include/tcp/TcpServer.hpp"
#include "../../../include/tcp/TcpClient.hpp"

#include <iostream>

bool breakRcv = false;

int main()
{
    gram::TcpServer server;

    server.AddReceivedHandler([](std::string msg){
        breakRcv = true;
    });

    server.Start();

    gram::TcpClient client;
    auto connection = client.CreateConnection("127.0.0.1", gram::TcpServer::STANDARD_PORT);
    connection->Open();
    connection->Send("Hello");

    while(!breakRcv){}

    return 0;
}