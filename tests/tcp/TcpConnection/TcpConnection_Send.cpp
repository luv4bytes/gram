#include "../../../include/tcp/TcpConnection.hpp"

int main()
{
    gram::TcpConnection con("localhost", 55556);
    con.Open();
 
    con.Send("Hello GitHub!");

    return 0;
}