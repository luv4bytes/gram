#include "../../../include/udp/UdpClient.hpp"

int main()
{
    gram::UdpClient client;

    auto con = client.CreateConnection("github.com", 80);
    client.OpenConnection(con);

    return 0;
}