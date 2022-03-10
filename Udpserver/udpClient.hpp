#pragma once

#include<iostream>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

class udpClient{
private:
    std::string ip;
    int port;
    int sock;
public:
    //ip,port? server
    udpClient(std::string _ip="127.0.0.1", int _port=8080)
        :ip(_ip), port(_port)
    {

    }
    //初始化
    void initClient(){
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        std::cout << "sock:" << sock << std::endl;
        //该数据未保存在内核栈上
       // struct sockaddr_in local;
       // local.sin_family = AF_INET;
       // local.sin_port = htons(port);
       // //地址转换,该参数为char*的，但是ip为stl的字符串类，因此要将c++风格的转换成c语言风格字符串
       // local.sin_addr.s_addr = inet_addr(ip.c_str());
       // //bind的第二个参数为sockaddr，但是传入的为sockaddr_in的，所以要加强制类型转换
       // if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
       //     std::cerr << "bind error!\n" << std::endl;
       //     exit(1);
       // }
    }
    //服务器start echo Client
    void start(){
        //char msg[64];
        std::string msg;
        struct sockaddr_in peer;
        peer.sin_family = AF_INET;
        //主机序列转网络序列
        peer.sin_port = htons(port);
        peer.sin_addr.s_addr = inet_addr(ip.c_str());
        for(;;){
            std::cout << "Please Enter#";
            std::cin >> msg;

            //发送数据
            sendto(sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));
            //收数据
            char echo[128];
            //谁发的，暂时不用
            struct sockaddr_in temp;
            ssize_t s = recvfrom(sock, echo, sizeof(echo)-1, 0, nullptr, nullptr);
            if(s > 0){
                echo[s] = 0;
                std::cout << "server#" << echo << std::endl;
            }
    //        msg[0] = '\0';
    //        struct sockaddr_in end_point;//远端发的
    //        //从sock上读数据，读到的数据放在msg中，长度，读写方式（0：阻塞方式）
    //        socklen_t len = sizeof(end_point);//len必须被初始化
    //        ssize_t s = recvfrom(sock, msg, sizeof(msg)-1, 0, (struct sockaddr*)&end_point, &len);
    //        if(s > 0){
    //            msg[s] = '\0';
    //            std::cout << "client #" << msg << std::endl;
    //            std::string echo_string = msg;
    //            echo_string += "[Client echo!]";
    //            sendto(sock, echo_string.c_str(), echo_string.size(), 0, (struct sockaddr*)&end_point, len);
    //        }
        }
    }
    ~udpClient(){
        close(sock);
    }
};










