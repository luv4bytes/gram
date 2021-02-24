cmake_minimum_required(VERSION 3.0.0)
project(gram VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(GRAM_VERSION="1.0")

add_executable(gram main.cpp
                    src/clientbase/ClientBase.cpp
                    src/clientbase/ClientBaseManager.cpp
                    src/tcp/TcpServer.cpp
                    src/tcp/TcpClient.cpp
                    src/udp/UdpServer.cpp
                    src/udp/UdpClient.cpp
                    src/serverbase/ServerBase.cpp
                    src/serverbase/ServerBaseManager.cpp
                    src/lua_api/LuaApi.cpp
                    src/commands/Commands.cpp
                    src/commands/Command.cpp
                    src/settings/ServerSettings.cpp
                    src/settings/SettingsInfo.cpp
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


# ########## ServerBase Tests ##########

add_executable(ServerBase_writeMessageToFile tests/serverbase/ServerBase/ServerBase_writeMessageToFile.cpp
                            src/serverbase/ServerBase.cpp
                            src/settings/ServerSettings.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(ServerBase_writeMessageToFile pthread)
target_link_libraries(ServerBase_writeMessageToFile uuid)
add_test(ServerBase_writeMessageToFile_Test ServerBase_writeMessageToFile)

add_executable(ServerBase_writeMessageToRingbuffer tests/serverbase/ServerBase/ServerBase_writeMessageToRingbuffer.cpp
                            src/serverbase/ServerBase.cpp
                            src/settings/ServerSettings.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(ServerBase_writeMessageToRingbuffer pthread)
target_link_libraries(ServerBase_writeMessageToRingbuffer uuid)
add_test(ServerBase_writeMessageToRingbuffer_Test ServerBase_writeMessageToRingbuffer)

# ########## ServerBaseManager Tests ##########

add_executable(ServerBaseManager_AddServer tests/serverbase/ServerBaseManager/ServerBaseManager_AddServer.cpp
                            src/tcp/TcpServer.cpp
                            src/udp/UdpServer.cpp
                            src/serverbase/ServerBase.cpp
                            src/serverbase/ServerBaseManager.cpp
                            src/settings/ServerSettings.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(ServerBaseManager_AddServer pthread)
target_link_libraries(ServerBaseManager_AddServer uuid)
add_test(ServerBaseManager_AddServer_Test ServerBaseManager_AddServer)

add_executable(ServerBaseManager_StopAllServers tests/serverbase/ServerBaseManager/ServerBaseManager_StopAllServers.cpp
                            src/tcp/TcpServer.cpp
                            src/serverbase/ServerBase.cpp
                            src/serverbase/ServerBaseManager.cpp
                            src/settings/ServerSettings.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(ServerBaseManager_StopAllServers pthread)
target_link_libraries(ServerBaseManager_StopAllServers uuid)
add_test(ServerBaseManager_StopAllServers_Test ServerBaseManager_StopAllServers)

add_executable(ServerBaseManager_PrintServers tests/serverbase/ServerBaseManager/ServerBaseManager_PrintServers.cpp
                            src/udp/UdpServer.cpp
                            src/serverbase/ServerBase.cpp
                            src/serverbase/ServerBaseManager.cpp
                            src/settings/ServerSettings.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(ServerBaseManager_PrintServers pthread)
target_link_libraries(ServerBaseManager_PrintServers uuid)
add_test(ServerBaseManager_PrintServers_Test ServerBaseManager_PrintServers)

add_executable(ServerBaseManager_RemoveServer tests/serverbase/ServerBaseManager/ServerBaseManager_RemoveServer.cpp
                            src/serverbase/ServerBase.cpp
                            src/serverbase/ServerBaseManager.cpp
                            src/settings/ServerSettings.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(ServerBaseManager_RemoveServer pthread)
target_link_libraries(ServerBaseManager_RemoveServer uuid)
add_test(ServerBaseManager_RemoveServer_Test ServerBaseManager_RemoveServer)

add_executable(ServerBaseManager_CleanUp tests/serverbase/ServerBaseManager/ServerBaseManager_CleanUp.cpp
                            src/tcp/TcpServer.cpp
                            src/udp/UdpServer.cpp
                            src/serverbase/ServerBase.cpp
                            src/serverbase/ServerBaseManager.cpp
                            src/settings/ServerSettings.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(ServerBaseManager_CleanUp pthread)
target_link_libraries(ServerBaseManager_CleanUp uuid)
add_test(ServerBaseManager_CleanUp_Test ServerBaseManager_CleanUp)

# ########## TcpClient Tests ##########

add_executable(TcpClient_Open tests/tcp/TcpClient/TcpClient_Open.cpp
                            src/clientbase/ClientBase.cpp
                            src/tcp/TcpClient.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(TcpClient_Open uuid)
add_test(TcpClient_Open_Test TcpClient_Open)

add_executable(TcpClient_Close tests/tcp/TcpClient/TcpClient_Close.cpp
                            src/clientbase/ClientBase.cpp
                            src/tcp/TcpClient.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(TcpClient_Close uuid)
add_test(TcpClient_Close_Test TcpClient_Close)

add_executable(TcpClient_SendFile tests/tcp/TcpClient/TcpClient_SendFile.cpp
                            src/clientbase/ClientBase.cpp
                            src/tcp/TcpClient.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(TcpClient_SendFile uuid)
add_test(TcpClient_SendFile_Test TcpClient_SendFile)

add_executable(TcpClient_SendText tests/tcp/TcpClient/TcpClient_SendText.cpp
                            src/clientbase/ClientBase.cpp
                            src/tcp/TcpClient.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(TcpClient_SendText uuid)
add_test(TcpClient_SendText_Test TcpClient_SendText)

# ########## UdpClient Tests ##########

add_executable(UdpClient_Open tests/udp/UdpClient/UdpClient_Open.cpp
                            src/clientbase/ClientBase.cpp
                            src/udp/UdpClient.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(UdpClient_Open uuid)
add_test(UdpClient_Open_Test UdpClient_Open)

add_executable(UdpClient_Close tests/udp/UdpClient/UdpClient_Close.cpp
                            src/clientbase/ClientBase.cpp
                            src/udp/UdpClient.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(UdpClient_Close uuid)
add_test(UdpClient_Close_Test UdpClient_Close)

# ########## Lua Tests ##########

add_executable(Lua_Initialize tests/lua_api/Lua_Initialize.cpp
                            src/lua_api/LuaApi.cpp
                            src/exceptions/GramException.cpp)
target_link_libraries(Lua_Initialize lua)
add_test(Lua_Initialize_Test Lua_Initialize)


# ########## Commands Tests ##########

add_executable(Commands_CreateCommands tests/commands/Commands_CreateCommands.cpp
                            src/clientbase/ClientBase.cpp
                            src/clientbase/ClientBaseManager.cpp
                            src/tcp/TcpClient.cpp
                            src/tcp/TcpServer.cpp
                            src/udp/UdpClient.cpp
                            src/udp/UdpServer.cpp
                            src/serverbase/ServerBase.cpp
                            src/serverbase/ServerBaseManager.cpp
                            src/commands/Commands.cpp
                            src/commands/Command.cpp
                            src/globals/Globals.cpp
                            src/settings/ServerSettings.cpp
                            src/settings/SettingsInfo.cpp
                            src/exceptions/GramException.cpp)

target_link_libraries(Commands_CreateCommands pthread)
target_link_libraries(Commands_CreateCommands uuid)
add_test(Commands_CreateCommands_Test Commands_CreateCommands)

# ########## Settings Tests ##########

add_executable(ServerSettings_PrintServerSettings tests/settings/ServerSettings/ServerSettings_PrintServerSettings.cpp
                            src/settings/ServerSettings.cpp
                            src/exceptions/GramException.cpp)
add_test(ServerSettings_PrintServerSettings_Test ServerSettings_PrintServerSettings)