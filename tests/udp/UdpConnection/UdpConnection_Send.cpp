#include "../../../include/udp/UdpConnection.hpp"

int main()
{
    UdpConnection con("github.com", 80);
    con.Open();
 
    con.Send("Hello GitHub!");

    return 0;
}