cmake_minimum_required(VERSION 3.0.0)
project(gram VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(gram main.cpp
                    src/TcpConnectionManager.cpp
                    src/TcpConnection.cpp
                    src/UdpConnectionManager.cpp
                    src/UdpConnection.cpp
                    src/GramException.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
