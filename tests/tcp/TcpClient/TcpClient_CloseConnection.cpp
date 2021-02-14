#include "../../../include/tcp/TcpClient.hpp"

int main()
{
    TcpClient client;

    auto con = client.CreateConnection("github.com", 80);
    client.OpenConnection(con);

    client.CloseConnection(con);

    return 0;
}