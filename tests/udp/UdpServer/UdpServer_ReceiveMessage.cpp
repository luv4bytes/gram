#include "../../../include/udp/UdpServer.hpp"
#include "../../../include/udp/UdpClient.hpp"

#include <iostream>

bool breakRcv = false;

int main()
{
    gram::UdpServer server;

    server.AddReceivedHandler([](std::string msg){
        breakRcv = true;
    });

    server.Start();

    gram::UdpClient client;
    auto connection = client.CreateConnection("127.0.0.1", gram::UdpServer::STANDARD_PORT);
    connection->Open();
    connection->Send("Hello");
    
    while(!breakRcv){}

    server.Stop();

    return 0;
}