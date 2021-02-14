#include "../../../include/udp/UdpClient.hpp"

int main()
{
    UdpClient client;

    auto con80 = client.CreateConnection("github.com", 80);
    auto con443 = client.CreateConnection("github.com", 443);

    client.OpenConnection(con80);
    client.OpenConnection(con443);

    client.CloseAllConnections();

    return 0;
}