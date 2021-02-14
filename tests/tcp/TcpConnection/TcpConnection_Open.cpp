#include "../../../include/tcp/TcpConnection.hpp"

int main()
{
    TcpConnection con("github.com", 80);
    con.Open();

    return 0;
}