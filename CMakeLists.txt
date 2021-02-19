cmake_minimum_required(VERSION 3.0.0)
project(gram VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)

add_executable(gram main.cpp
                    src/tcp/TcpClient.cpp
                    src/tcp/TcpConnection.cpp
                    src/tcp/TcpServer.cpp
                    src/tcp/TcpManager.cpp
                    src/udp/UdpClient.cpp
                    src/udp/UdpConnection.cpp
                    src/udp/UdpServer.cpp
                    src/udp/UdpManager.cpp
                    src/lua_api/LuaApi.cpp
                    src/commands/Commands.cpp
                    src/commands/Command.cpp
                    src/globals/Globals.cpp
                    src/exceptions/GramException.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(gram uuid)
target_link_libraries(gram pthread)
target_link_libraries(gram lua)

include(CTest)
enable_testing()


# ########## TcpClient Tests ##########

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


# ########## TcpConnection Tests ##########

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


# ########## TcpServer Tests ##########

add_executable(TcpServer_ReceiveMessage tests/tcp/TcpServer/TcpServer_ReceiveMessage.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(TcpServer_ReceiveMessage pthread)
target_link_libraries(TcpServer_ReceiveMessage uuid)
add_test(TcpServer_ReceiveMessage_Test TcpServer_ReceiveMessage)

# ########## TcpManager Tests ##########

add_executable(TcpManager_AddServer tests/tcp/TcpManager/TcpManager_AddServer.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/tcp/TcpManager.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(TcpManager_AddServer pthread)
target_link_libraries(TcpManager_AddServer uuid)
add_test(TcpManager_AddServer_Test TcpManager_AddServer)

add_executable(TcpManager_AddClient tests/tcp/TcpManager/TcpManager_AddClient.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/tcp/TcpManager.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(TcpManager_AddClient pthread)
target_link_libraries(TcpManager_AddClient uuid)
add_test(TcpManager_AddClient_Test TcpManager_AddClient)

add_executable(TcpManager_StopAllServers tests/tcp/TcpManager/TcpManager_StopAllServers.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/tcp/TcpManager.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(TcpManager_StopAllServers pthread)
target_link_libraries(TcpManager_StopAllServers uuid)
add_test(TcpManager_StopAllServers_Test TcpManager_StopAllServers)

add_executable(TcpManager_CloseAllClients tests/tcp/TcpManager/TcpManager_CloseAllClients.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/tcp/TcpManager.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(TcpManager_CloseAllClients pthread)
target_link_libraries(TcpManager_CloseAllClients uuid)
add_test(TcpManager_CloseAllClients_Test TcpManager_CloseAllClients)

add_executable(TcpManager_PrintServers tests/tcp/TcpManager/TcpManager_PrintServers.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/tcp/TcpManager.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(TcpManager_PrintServers pthread)
target_link_libraries(TcpManager_PrintServers uuid)
add_test(TcpManager_PrintServers_Test TcpManager_PrintServers)

add_executable(TcpManager_RemoveServer tests/tcp/TcpManager/TcpManager_RemoveServer.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/tcp/TcpManager.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(TcpManager_RemoveServer pthread)
target_link_libraries(TcpManager_RemoveServer uuid)
add_test(TcpManager_RemoveServer_Test TcpManager_RemoveServer)

add_executable(TcpManager_CleanUp tests/tcp/TcpManager/TcpManager_CleanUp.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/tcp/TcpManager.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(TcpManager_CleanUp pthread)
target_link_libraries(TcpManager_CleanUp uuid)
add_test(TcpManager_CleanUp_Test TcpManager_CleanUp)

# ########## UdpClient Tests ##########

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


# ########## UdpConnection Tests ##########

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


# ########## UdpServer Tests ##########

add_executable(UdpServer_ReceiveMessage tests/udp/UdpServer/UdpServer_ReceiveMessage.cpp
                            src/udp/UdpServer.cpp
                            src/udp/UdpClient.cpp
                            src/udp/UdpConnection.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(UdpServer_ReceiveMessage uuid)
target_link_libraries(UdpServer_ReceiveMessage pthread)
add_test(UdpServer_ReceiveMessage_Test UdpServer_ReceiveMessage)


# ########## Lua Tests ##########

add_executable(Lua_Initialize tests/lua_api/Lua_Initialize.cpp
                            src/lua_api/LuaApi.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(Lua_Initialize lua)
add_test(Lua_Initialize_Test Lua_Initialize)


# ########## Commands Tests ##########

add_executable(Commands_CreateCommands tests/commands/Commands_CreateCommands.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpConnection.cpp
                            src/tcp/TcpServer.cpp
                            src/tcp/TcpManager.cpp
                            src/udp/UdpClient.cpp
                            src/udp/UdpConnection.cpp
                            src/udp/UdpServer.cpp
                            src/udp/UdpManager.cpp
                            src/commands/Commands.cpp
                            src/commands/Command.cpp
                            src/globals/Globals.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(Commands_CreateCommands pthread)
target_link_libraries(Commands_CreateCommands uuid)
add_test(Commands_CreateCommands_Test Commands_CreateCommands)