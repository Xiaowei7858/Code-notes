#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include<iostream>
#include<unistd.h>
#include<string>
#include<cstdlib>
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>

#define BACKLOG 5

class tcpServer{
private:
    int port;
    int lsock;//监听套接字
public:
    tcpServer(int _port):port(_port), lsock(-1)
    {}

    void initServer(){
        signal(SIGCHLD, SIG_IGN); //父进程忽略子进程发来的信号
        lsock = socket(AF_INET, SOCK_STREAM, 0);
        if(lsock < 0){
            std::cerr << "socket error" << std::endl;
            exit(2);
        }
        struct sockaddr_in local;
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(lsock, (struct sockaddr*)&local, sizeof(local)) < 0){
            std::cerr << "bind error" << std::endl;
            exit(3);
        }
        if(listen(lsock, BACKLOG) < 0){
            std::cerr << "bind error" << std::endl;
            exit(4);
        }
    }

    void service(int sock){
        char buffer[1024];
        while(true){
            //read or wirte -> ok!
           size_t s = recv(sock, buffer, sizeof(buffer)-1, 0);
           if(s > 0){
               buffer[s] = 0;
               std::cout << "client#" << buffer << std::endl;

               send(sock, buffer, strlen(buffer), 0);
           }
           if(s == 0){
               std::cout << "client quit ... " << std::endl;
               close(sock);
               break;
           }
           else{
               std::cout << "recv client data error ... " << std::endl;
               break;
           }
        }
        close(sock);
    }

    void start(){
        sockaddr_in endpoint;
        while(true){
            socklen_t len = sizeof(endpoint);
            //获取连接
            int sock = accept(lsock, (struct sockaddr*)&endpoint, &len);
            if(sock < 0){
                std::cerr << "accept error" << std::endl;
                continue;
            }
            //打印客户端ip和端口号
            std::string cli_info = inet_ntoa(endpoint.sin_addr);
            cli_info += ":";
            cli_info += std::to_string(ntohs(endpoint.sin_port));
            std::cout << "get a new link ... " << cli_info << " sock: " << sock << std::endl;
            
            pid_t id = fork();
            if(id == 0){
                //防止子进程和父进程访问同一个文件,防止访问同一个文件符表
                close(lsock);
                service(sock);
                //当父进程accept时，子进程有可能已经服务完毕了，子进程有可能继续往下运行，因此
                exit(0);
            }

            //父进程只关心连接，如果不关闭sock文件描述符，后面文件描述符只会越来越少
            close(sock);
            //不能等待，会阻塞, 但是子进程退出会产生僵尸，怎么办？当父进程忽略子进程发来的signal，系统会自动回收子进程
        }
    }

    ~tcpServer(){}
};

#endif
