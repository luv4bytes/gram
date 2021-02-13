#include <iostream>

#include "include/tcp/TcpClient.hpp"
#include "include/tcp/TcpServer.hpp"

#include "include/udp/UdpClient.hpp"

int main(int argc, char** argv)
{
    try
    {
        std::cout << "Welcome to gram!" << std::endl;

        TcpClient tcpClient;
        TcpServer tcpServer;

        tcpServer.Start();

        tcpServer.Stop();

        UdpClient udpClient;

        return 0;
    }
    catch(const GramException& e)
    {
        std::cerr << e.ErrorMessage << '\n';
    }
}
