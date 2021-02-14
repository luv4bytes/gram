#include "../../../include/tcp/TcpConnection.hpp"

int main()
{
    TcpConnection con("github.com", 80);
    con.Open();
    con.Close();

    return 0;
}