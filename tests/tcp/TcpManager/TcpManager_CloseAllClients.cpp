#include "../../../include/tcp/TcpManager.hpp"

int main()
{
    gram::TcpManager manager;
    gram::TcpClient* client = new gram::TcpClient();

    manager.AddClient(client);

    client->CreateConnection("github.com", 80)->Open();

    manager.CloseAllClients();

    return 0;
}