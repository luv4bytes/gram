#include "../../../include/udp/UdpManager.hpp"

int main()
{
    gram::UdpManager manager;
    gram::UdpServer* server = new gram::UdpServer();

    manager.AddServer(server);

    manager.PrintServers();

    return 0;
}