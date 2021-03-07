#include "../../../include/serverbase/ServerBaseManager.hpp"

int main()
{
    gram::ServerBaseManager manager;
    std::shared_ptr<gram::ServerBase> server = std::shared_ptr<gram::ServerBase>(new gram::ServerBase());

    manager.AddServer(server);
    manager.RemoveServer(server);

    return 0;
}