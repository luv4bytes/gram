#include <iostream>

#include "include/TcpConnectionManager.hpp"
#include "include/UdpConnectionManager.hpp"

int main(int argc, char** argv) {

    try
    {
        TcpConnectionManager tcpManager;
        UdpConnectionManager udpManager;

        return 0;
    }
    catch(const GramException& e)
    {
        std::cerr << e.ErrorMessage << '\n';
    }
}
