#include "../../../include/serverbase/ServerBaseManager.hpp"
#include "../../../include/tcp/TcpServer.hpp"

int main()
{
    gram::ServerBaseManager manager;
    std::shared_ptr<gram::ServerBase> server = std::shared_ptr<gram::ServerBase>(new gram::TcpServer());

    manager.AddServer(server);

    server->Start();

    manager.StopAllServers();

    return 0;
}