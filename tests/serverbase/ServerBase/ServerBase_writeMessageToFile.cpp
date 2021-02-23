#include "../../../include/serverbase/ServerBase.hpp"

int main()
{
    gram::ServerBase* server = new gram::ServerBase();

    server->Settings.OutputFile.Value = "./test.txt";
    server->WriteMessageToFile("This\n");
    server->WriteMessageToFile("is\n");
    server->WriteMessageToFile("a\n");
    server->WriteMessageToFile("message\n");

    return 0;
}