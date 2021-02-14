#include "../../../include/udp/UdpConnection.hpp"

int main()
{
    UdpConnection con("github.com", 80);
    con.Open();

    return 0;
}