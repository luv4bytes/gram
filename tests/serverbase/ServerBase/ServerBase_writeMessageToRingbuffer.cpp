#include "../../../include/serverbase/ServerBase.hpp"

int main()
{
    gram::ServerBase* server = new gram::ServerBase();

    server->WriteMessageToRingbuffer("This\n");
    server->WriteMessageToRingbuffer("is\n");
    server->WriteMessageToRingbuffer("a\n");
    server->WriteMessageToRingbuffer("message\n");

    return 0;
}