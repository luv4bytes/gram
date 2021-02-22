#include "../../../include/serverbase/ServerBaseManager.hpp"
#include "../../../include/tcp/TcpServer.hpp"

int main()
{
    gram::ServerBaseManager manager;
    gram::ServerBase* server = new gram::TcpServer();

    manager.AddServer(server);

    server->Start();

    manager.StopAllServers();

    return 0;
}