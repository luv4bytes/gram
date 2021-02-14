#include "../../../include/tcp/TcpClient.hpp"

int main()
{
    TcpClient client;

    auto con80 = client.CreateConnection("216.58.213.206", 80);
    auto con443 = client.CreateConnection("216.58.213.206", 443);

    client.OpenConnection(con80);
    client.OpenConnection(con443);

    client.CloseAllConnections();

    return 0;
}