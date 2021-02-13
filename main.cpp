#include <iostream>

#include "include/tcp/TcpConnectionManager.hpp"
#include "include/udp/UdpConnectionManager.hpp"

int main(int argc, char** argv) {

    try
    {
        std::cout << "Welcome to gram!" << std::endl;

        TcpConnectionManager tcpManager;
        UdpConnectionManager udpManager;

        return 0;
    }
    catch(const GramException& e)
    {
        std::cerr << e.ErrorMessage << '\n';
    }
}
