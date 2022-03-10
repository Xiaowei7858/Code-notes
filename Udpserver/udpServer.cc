#include"udpServer.hpp"

int main()
{
    udpServer *up = new udpServer();
    up->initServer();
    up->start();
    return 0;
}
