#include "../../../include/tcp/TcpClient.hpp"

int main()
{
    gram::TcpClient client("github.com", 80);

    client.Open();

    client.SendText("Hello GitHub!");

    client.Close();

    return 0;
}