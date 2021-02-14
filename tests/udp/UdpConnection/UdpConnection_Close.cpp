#include "../../../include/udp/UdpConnection.hpp"

int main()
{
    UdpConnection con("216.58.213.206", 80);
    con.Open();
    con.Close();

    return 0;
}