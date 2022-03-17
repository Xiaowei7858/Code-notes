#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include<iostream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

class tcpClient{
private:
    std::string svr_ip; //服务器ip,域名就是ip
    int svr_port; //服务器端口号
    int sock;
public:
    //默认ip和端口号是本地环回
    tcpClient(std::string _ip="127.0.0.1", int _port = 8080)
        :svr_ip(_ip), svr_port(_port)
    {}

    void initClient(){
        //通信协议，底层技术都是套接字，所以要创建套接字，IPV4，流式套接, 0:tcp
        sock = socket(AF_INET, SOCK_STREAM, 0);
        //创建失败
        if(sock < 0){
            std::cerr << "socket error" << std::endl;
            //本质是把进程退出
            exit(2);
        }
        //连接服务器
        struct sockaddr_in svr;
        svr.sin_family = AF_INET;
        //主机转网络系列
        svr.sin_port = htons(svr_port);
        //点分十进制的字符串风格地址转换4字节ip，且转换成对应的网络序列
        svr.sin_addr.s_addr = inet_addr(svr_ip.c_str());
        if(connect(sock, (struct sockaddr*)&svr, sizeof(svr)) != 0){
            std::cerr << "connect error" << std::endl;
        }
        //connect success;
    }

    void start(){
        char msg[64];
        while(true){
            std::cout << "Please Enter Message #";
            fflush(stdout);
            //从0的位置读
            size_t s = read(0, msg, sizeof(msg)-1);
            //读取成功
            if(s > 0){
                //发送出去
                msg[s] = 0;
                //往哪发，发什么，多长
                send(sock, msg, strlen(msg), 0);
                //读 服务器返回的数据
                size_t ss = recv(sock, msg, sizeof(msg)-1, 0);
                if(ss > 0){
                    msg[ss] = 0;
                    std::cout << "server echo # " << msg << std::endl;
                }
            }
        }
    }

    ~tcpClient(){
        close(sock);
    }


};

#endif

