#include "../../../include/tcp/TcpClient.hpp"

int main()
{
    gram::TcpClient client;

    auto con = client.CreateConnection("github.com", 80);
    client.OpenConnection(con);

    client.CloseConnection(con);

    return 0;
}