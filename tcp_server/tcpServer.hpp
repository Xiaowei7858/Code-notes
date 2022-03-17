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
        //套接字信息、写入用户层
        struct sockaddr_in local;
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        //INADDR_ANY:绑定任意ip
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        //绑定，套接字信息填入内核里面
        //创建套接字，创建的是文件相关的信息，绑定是文件信息与网络信息进行绑定
        if(bind(lsock, (struct sockaddr*)&local, sizeof(local)) < 0){
            std::cerr << "bind error" << std::endl;
            exit(3);
        }
        //将套接字设置为监听状态
        //第二个参数代表的是底层在接收新链接请求时，底层所维护的全链接队列的长度
        if(listen(lsock, BACKLOG) < 0){
            std::cerr << "bind error" << std::endl;
            exit(4);
        }
    }

    //当客户端退出时，1.知道客户端退出了 2.服务器从while循环中退出 3.服务器关闭掉刚刚新来的链接所打开的套接字

    //io服务:先读取数据，然后将读取的数据发送出去
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
               //客户端退出了，服务器退出，关闭套接字(不关闭，所能使用的文件描述符会越来越少，默认有32个(其实大得多，还有扩展表))
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

    void *serviceRoutine(void* arg){

    }

    void start(){
        sockaddr_in endpoint;
        //常驻进程
        while(true){
            socklen_t len = sizeof(endpoint);
            //获取连接
            int sock = accept(lsock, (struct sockaddr*)&endpoint, &len);
            if(sock < 0){
                std::cerr << "accept error" << std::endl;
                continue;
            }
            //打印客户端ip和端口号
            //inet_nota:四字节ip转换成点分十进制的ip
            std::string cli_info = inet_ntoa(endpoint.sin_addr);
            cli_info += ":";
            cli_info += std::to_string(ntohs(endpoint.sin_port));
            std::cout << "get a new link ... " << cli_info << " sock: " << sock << std::endl;
            
            pthread_t tid;
            pthread_create(&tid, nullptr, serviceRoutine, (void*)&sock);
            //pid_t id = fork();
            //if(id == 0){
            //    //防止子进程和父进程访问同一个文件,防止访问同一个文件符表
            //    close(lsock);
            //    //进行io服务
            //    service(sock);
            //    //当父进程accept时，子进程有可能已经服务完毕了，子进程有可能继续往下运行，因此
            //    exit(0);
            //}

            ////父进程只关心连接，如果不关闭sock文件描述符，后面文件描述符只会越来越少
            //close(sock);
            //不能等待，会阻塞, 但是子进程退出会产生僵尸，怎么办？当父进程忽略子进程发来的signal，系统会自动回收子进程
            
            //不推荐，fork会消耗大量资源
           // if(id == 0){
           //     if(fork() > 0){
           //         exit(0);
           //     }

           //     close(lsock);
           //     service(sock);
           //     exit(0);
           // }

           // close(sock);
           // waitpid(id, NULL, 0);
        }
    }

    ~tcpServer(){}
};

#endif
