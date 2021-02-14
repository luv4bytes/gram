cmake_minimum_required(VERSION 3.0.0)
project(gram VERSION 0.1.0)

add_executable(gram main.cpp
                    src/tcp/TcpClient.cpp
                    src/tcp/TcpConnection.cpp
                    src/tcp/TcpServer.cpp
                    src/udp/UdpClient.cpp
                    src/udp/UdpConnection.cpp
                    src/udp/UdpServer.cpp
                    src/exceptions/GramException.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(gram pthread)

include(CTest)
enable_testing()


# ########## TcpClient tests ##########

add_executable(TcpClient_CreateConnection tests/tcp/TcpClient/TcpClient_CreateConnection.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(TcpClient_CreateConnection_Test TcpClient_CreateConnection)

add_executable(TcpClient_OpenConnection tests/tcp/TcpClient/TcpClient_OpenConnection.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(TcpClient_OpenConnection_Test TcpClient_OpenConnection)

add_executable(TcpClient_CloseConnection tests/tcp/TcpClient/TcpClient_CloseConnection.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(TcpClient_CloseConnection_Test TcpClient_CloseConnection)

add_executable(TcpClient_CloseAllConnections tests/tcp/TcpClient/TcpClient_CloseAllConnections.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(TcpClient_CloseAllConnections_Test TcpClient_CloseAllConnections)


# ########## TcpConnection tests ##########

add_executable(TcpConnection_Open tests/tcp/TcpConnection/TcpConnection_Open.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(TcpConnection_Open_Test TcpConnection_Open)

add_executable(TcpConnection_Close tests/tcp/TcpConnection/TcpConnection_Close.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(TcpConnection_Close_Test TcpConnection_Close)

add_executable(TcpConnection_Send tests/tcp/TcpConnection/TcpConnection_Send.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(TcpConnection_Send_Test TcpConnection_Send)


# ########## TcpServer tests ##########

add_executable(TcpServer_ReceiveMessage tests/tcp/TcpServer/TcpServer_ReceiveMessage.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(TcpServer_ReceiveMessage pthread)
add_test(TcpServer_ReceiveMessage_Test TcpServer_ReceiveMessage)

# ########## UdpClient tests ##########

add_executable(UdpClient_CreateConnection tests/udp/UdpClient/UdpClient_CreateConnection.cpp
                            src/udp/UdpClient.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(UdpClient_CreateConnection_Test UdpClient_CreateConnection)

add_executable(UdpClient_OpenConnection tests/udp/UdpClient/UdpClient_OpenConnection.cpp
                            src/udp/UdpClient.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(UdpClient_OpenConnection_Test UdpClient_OpenConnection)

add_executable(UdpClient_CloseConnection tests/udp/UdpClient/UdpClient_CloseConnection.cpp
                            src/udp/UdpClient.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(UdpClient_CloseConnection_Test UdpClient_CloseConnection)

add_executable(UdpClient_CloseAllConnections tests/udp/UdpClient/UdpClient_CloseAllConnections.cpp
                            src/udp/UdpClient.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(UdpClient_CloseAllConnections_Test UdpClient_CloseAllConnections)


# ########## UdpConnection tests ##########

add_executable(UdpConnection_Open tests/udp/UdpConnection/UdpConnection_Open.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(UdpConnection_Open_Test UdpConnection_Open)

add_executable(UdpConnection_Close tests/udp/UdpConnection/UdpConnection_Close.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(UdpConnection_Close_Test UdpConnection_Close)

add_executable(UdpConnection_Send tests/udp/UdpConnection/UdpConnection_Send.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)
add_test(UdpConnection_Send_Test UdpConnection_Send)


# ########## UdpServer tests ##########

add_executable(UdpServer_ReceiveMessage tests/udp/UdpServer/UdpServer_ReceiveMessage.cpp
                            src/udp/UdpServer.cpp
                            src/udp/UdpClient.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(UdpServer_ReceiveMessage pthread)
add_test(UdpServer_ReceiveMessage_Test UdpServer_ReceiveMessage)