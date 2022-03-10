#pragma once

#include<iostream>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

class udpServer{
private:
    std::string ip;
    int port;
    int sock;
public:
    udpServer(std::string _ip="127.0.0.1", int _port=8080)
        :ip(_ip), port(_port)
    {

    }
    //初始化
    void initServer(){
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        std::cout << "sock:" << sock << std::endl;
        //该数据未保存在内核栈上
        struct sockaddr_in local;
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        //地址转换,该参数为char*的，但是ip为stl的字符串类，因此要将c++风格的转换成c语言风格字符串
        local.sin_addr.s_addr = inet_addr(ip.c_str());
        //bind的第二个参数为sockaddr，但是传入的为sockaddr_in的，所以要加强制类型转换
        if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
            std::cerr << "bind error!\n" << std::endl;
            exit(1);
        }
    }
    //服务器start echo server
    void start(){
        char msg[64];
        for(;;){
            msg[0] = '\0';
            struct sockaddr_in end_point;//远端发的
            //从sock上读数据，读到的数据放在msg中，长度，读写方式（0：阻塞方式）
            socklen_t len = sizeof(end_point);//len必须被初始化
            ssize_t s = recvfrom(sock, msg, sizeof(msg)-1, 0, (struct sockaddr*)&end_point, &len);
            if(s > 0){
                msg[s] = '\0';
                std::cout << "client #" << msg << std::endl;
                std::string echo_string = msg;
                echo_string += "[server echo!]";
                sendto(sock, echo_string.c_str(), echo_string.size(), 0, (struct sockaddr*)&end_point, len);
            }
        }
    }
    ~udpServer(){
        close(sock);
    }
};










