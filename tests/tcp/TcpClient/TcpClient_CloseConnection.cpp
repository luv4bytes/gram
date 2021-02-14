#include "../../../include/tcp/TcpClient.hpp"

int main()
{
    TcpClient client;

    auto con = client.CreateConnection("216.58.213.206", 80);
    client.OpenConnection(con);

    client.CloseConnection(con);

    return 0;
}