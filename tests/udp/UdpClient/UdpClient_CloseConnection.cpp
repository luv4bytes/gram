#include "../../../include/udp/UdpClient.hpp"

int main()
{
    UdpClient client;

    auto con = client.CreateConnection("216.58.213.206", 80);
    client.CloseConnection(con);

    return 0;
}