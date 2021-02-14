#include "../../../include/udp/UdpClient.hpp"

int main()
{
    UdpClient client;

    auto connectionBlank = client.CreateConnection();
    auto connection = client.CreateConnection("testserver", 80);

    return 0;
}