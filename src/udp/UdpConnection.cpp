#include "../../include/udp/UdpConnection.hpp"

UdpConnection::UdpConnection()
{
}

UdpConnection::UdpConnection(std::string endpointIpOrName, int port)
{
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);

    if (socketFd == -1)
        throw GramException("Error creating socket -> " + std::string(strerror(errno)));

    EndpointIpOrName = endpointIpOrName;
    Port = port;
}

UdpConnection::~UdpConnection()
{
}

void UdpConnection::Open()
{
    struct addrinfo* addresses;

    int gotInfo = getaddrinfo(EndpointIpOrName.c_str(), std::to_string(Port).c_str(), nullptr, &addresses);

    if (gotInfo != 0)
        throw GramException("Error getting address information -> " + std::string(gai_strerror(gotInfo)));
    
    struct addrinfo* target = addresses->ai_next;

    int connected = connect(socketFd, target->ai_addr, target->ai_addrlen);

    if (connected == -1)
        throw GramException("Error connecting to target -> " + std::string(strerror(errno)));
}

void UdpConnection::Close()
{
    if (socketFd == 0)
        return;        
    
    int closed = close(socketFd);

    if (closed == -1)
        throw GramException("Error closing socket -> " + std::string(strerror(errno)));
}

void UdpConnection::Send(std::string message)
{
    if (message.empty())
        return;

    int sent = send(socketFd, message.c_str(), message.length(), 0);

    if (sent == -1)
        throw GramException("Error sending message -> " + std::string(strerror(errno)));
}