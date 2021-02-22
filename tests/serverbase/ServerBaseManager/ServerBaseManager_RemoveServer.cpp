#include "../../../include/serverbase/ServerBaseManager.hpp"

int main()
{
    gram::ServerBaseManager manager;
    gram::ServerBase* server = new gram::ServerBase();

    manager.RemoveServer(server);

    return 0;
}