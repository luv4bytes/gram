#include "../../../include/tcp/TcpManager.hpp"

int main()
{
    gram::TcpManager manager;
    gram::TcpServer* server = new gram::TcpServer();

    manager.AddServer(server);

    manager.PrintServers();

    return 0;
}