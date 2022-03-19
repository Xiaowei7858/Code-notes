#include "httpServer.hpp"

static void Usage(std::string proc){
    std::cout << "Usage \t";
    std::cout << proc << "port" << std::endl;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        Usage(argv[0]);
        exit(1);
    }

    HttpServer *hp = new HttpServer(atoi(argv[1]));
    hp->InitServer();
    hp->Start();

    return 0;
}
