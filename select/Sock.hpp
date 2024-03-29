#pragma once

#include<iostream>
#include<string>

#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>

#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/select.h>

#define DFL_PORT 8080
using namespace std;

class Sock{
public:
    static int Socket(){
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0){
            cerr << "socket error" << endl;
            exit(2);
        }

        return sock;
    }

    static void Bind(int sock, int port){
        struct sockaddr_in local;
        //对内存做清空
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
            cerr << "bind error" << endl;
            exit(3);
        }
    }

    static void Listen(int sock){
        if(listen(sock, 5) < 0){
            cerr << "listen error" << endl;
            exit(4);
        }
    }

    static int Accept(int sock){
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int fd = accept(sock, (struct sockaddr*)&peer, &len);
        if(fd < 0){
            cerr << "accept error" << endl;
        }

        return fd;
    }

    static void Setsockopt(int sock){
        //setsockopt();
        int opt = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    }
};

