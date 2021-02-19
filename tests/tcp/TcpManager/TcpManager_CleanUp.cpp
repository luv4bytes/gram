#include "../../../include/tcp/TcpManager.hpp"

int main()
{
    gram::TcpManager manager;
    gram::TcpServer* server = new gram::TcpServer();
    gram::TcpClient* client = new gram::TcpClient();

    server->Start();
    
    client->CreateConnection("github.com", 80)->Open();

    manager.AddServer(server);
    manager.AddClient(client);

    manager.CleanUp();

    return 0;
}