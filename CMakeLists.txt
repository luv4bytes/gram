cmake_minimum_required(VERSION 3.0.0)
project(gram VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(gram main.cpp
                    src/tcp/TcpClient.cpp
                    src/tcp/TcpConnection.cpp
                    src/tcp/TcpServer.cpp
                    src/udp/UdpClient.cpp
                    src/udp/UdpConnection.cpp
                    src/GramException.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
