#include "../../../include/tcp/TcpConnection.hpp"

int main()
{
    gram::TcpConnection con("github.com", 80);
    con.Open();
    con.Close();

    return 0;
}