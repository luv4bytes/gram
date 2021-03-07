#include "../../../include/serverbase/ServerBaseManager.hpp"
#include "../../../include/tcp/TcpServer.hpp"
#include "../../../include/udp/UdpServer.hpp"

int main()
{
    gram::ServerBaseManager manager;

    std::shared_ptr<gram::TcpServer> serverTcp = std::shared_ptr<gram::TcpServer>(new gram::TcpServer());
    serverTcp->Start();
    manager.AddServer(serverTcp);

    std::shared_ptr<gram::UdpServer> serverUdp = std::shared_ptr<gram::UdpServer>(new gram::UdpServer());
    serverUdp->Start();
    manager.AddServer(serverUdp);

    manager.CleanUp();

    return 0;
}