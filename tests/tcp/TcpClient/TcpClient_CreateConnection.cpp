#include "../../../include/tcp/TcpClient.hpp"

int main()
{
    TcpClient client;

    auto connectionBlank = client.CreateConnection();
    auto connection = client.CreateConnection("github.com", 80);

    return 0;
}