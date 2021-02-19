#include "../../../include/udp/UdpManager.hpp"

int main()
{
    gram::UdpManager manager;
    gram::UdpServer* server = new gram::UdpServer();

    manager.AddServer(server);

    server->Start();

    manager.StopAllServers();

    return 0;
}