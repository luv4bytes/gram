#include "../../../include/serverbase/ServerBase.hpp"

int main()
{
    gram::ServerBase* server = new gram::ServerBase();

    server->Settings.OutputFile.Value = "./test.txt";
    server->writeMessageToFile("This\n");
    server->writeMessageToFile("is\n");
    server->writeMessageToFile("a\n");
    server->writeMessageToFile("message\n");

    return 0;
}