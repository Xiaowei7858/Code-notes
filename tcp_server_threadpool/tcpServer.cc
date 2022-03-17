#include "tcpServer.hpp"

static void Usage(std::string proc){
    std::cout << "Usage: " << std::endl;
    std::cout << '\t' << proc << "port" << std::endl;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        Usage(argv[0]);
        exit(1);
    }
    tcpServer * tcp = new tcpServer(atoi(argv[1]));
    tcp->initServer();
    tcp->start();
    
    delete tcp;
    return 0;
}
