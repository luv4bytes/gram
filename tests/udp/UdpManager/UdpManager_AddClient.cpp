#include "../../../include/udp/UdpManager.hpp"

int main()
{
    gram::UdpManager manager;
    gram::UdpClient* client = new gram::UdpClient();

    manager.AddClient(client);

    return 0;
}