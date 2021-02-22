#include "../../../include/serverbase/ServerBase.hpp"

int main()
{
    gram::ServerBase* server = new gram::ServerBase();

    server->writeMessageToRingbuffer("This\n");
    server->writeMessageToRingbuffer("is\n");
    server->writeMessageToRingbuffer("a\n");
    server->writeMessageToRingbuffer("message\n");

    return 0;
}