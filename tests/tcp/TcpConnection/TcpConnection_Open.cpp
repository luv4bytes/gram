#include "../../../include/tcp/TcpConnection.hpp"

int main()
{
    TcpConnection con("216.58.213.206", 80);
    con.Open();

    return 0;
}