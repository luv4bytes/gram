#include "../../../include/serverbase/ServerBaseManager.hpp"
#include "../../../include/udp/UdpServer.hpp"

int main()
{
    gram::ServerBaseManager manager;
    std::shared_ptr<gram::UdpServer> server = std::shared_ptr<gram::UdpServer>(new gram::UdpServer());

    manager.AddServer(server);

    manager.PrintServers();

    return 0;
}