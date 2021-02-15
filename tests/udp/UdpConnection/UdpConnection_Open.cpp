#include "../../../include/udp/UdpConnection.hpp"

int main()
{
    gram::UdpConnection con("github.com", 80);
    con.Open();

    return 0;
}