#include "../../../include/udp/UdpManager.hpp"

int main()
{
    gram::UdpManager manager;
    gram::UdpClient* client = new gram::UdpClient();

    manager.AddClient(client);

    client->CreateConnection("github.com", 80)->Open();

    manager.CloseAllClients();

    return 0;
}