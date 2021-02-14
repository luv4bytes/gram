#include "../../../include/udp/UdpServer.hpp"
#include "../../../include/udp/UdpClient.hpp"

#include <iostream>

bool breakRcv = false;

int main()
{
    UdpServer server;

    server.AddReceivedHandler([](std::string msg){
        breakRcv = true;
    });

    server.Start();

    UdpClient client;
    auto connection = client.CreateConnection("127.0.0.1", UdpServer::STANDARD_PORT);
    connection->Open();
    connection->Send("Hello");
    
    while(!breakRcv){}

    return 0;
}