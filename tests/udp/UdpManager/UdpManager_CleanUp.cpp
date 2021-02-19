#include "../../../include/udp/UdpManager.hpp"

int main()
{
    gram::UdpManager manager;
    gram::UdpServer* server = new gram::UdpServer();
    gram::UdpClient* client = new gram::UdpClient();

    server->Start();
    
    client->CreateConnection("github.com", 80)->Open();

    manager.AddServer(server);
    manager.AddClient(client);

    manager.CleanUp();

    return 0;
}