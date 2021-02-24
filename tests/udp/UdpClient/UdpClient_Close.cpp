#include "../../../include/udp/UdpClient.hpp"

int main()
{
    gram::UdpClient client("github.com", 80);

    client.Open();

    client.Close();

    return 0;
}