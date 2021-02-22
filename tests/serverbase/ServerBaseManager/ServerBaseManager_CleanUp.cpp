#include "../../../include/serverbase/ServerBaseManager.hpp"
#include "../../../include/tcp/TcpServer.hpp"
#include "../../../include/udp/UdpServer.hpp"

int main()
{
    gram::ServerBaseManager manager;

    gram::TcpServer* serverTcp = new gram::TcpServer();
    serverTcp->Start();
    manager.AddServer(serverTcp);

    gram::UdpServer* serverUdp = new gram::UdpServer();
    serverUdp->Start();
    manager.AddServer(serverUdp);

    manager.CleanUp();

    return 0;
}