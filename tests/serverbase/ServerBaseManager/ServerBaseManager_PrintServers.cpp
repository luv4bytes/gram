#include "../../../include/serverbase/ServerBaseManager.hpp"
#include "../../../include/udp/UdpServer.hpp"

int main()
{
    gram::ServerBaseManager manager;
    gram::UdpServer* server = new gram::UdpServer();

    manager.AddServer(server);

    manager.PrintServers();

    return 0;
}