#include "../../../include/tcp/TcpManager.hpp"

int main()
{
    gram::TcpManager manager;
    gram::TcpClient* client = new gram::TcpClient();

    manager.AddClient(client);

    return 0;
}