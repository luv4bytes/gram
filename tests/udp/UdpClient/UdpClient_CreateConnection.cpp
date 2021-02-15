#include "../../../include/udp/UdpClient.hpp"

int main()
{
    gram::UdpClient client;

    auto connectionBlank = client.CreateConnection();
    auto connection = client.CreateConnection("github.com", 80);

    return 0;
}