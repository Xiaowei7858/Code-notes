#pragma once

#include"Sock.hpp"

using namespace std;
#define DFL_PORT 8080
#define NUM (sizeof(fd_set)*8)

class SelectServer{
private:
    int lsock; //listen sock
    int port;
    int fd_array[NUM]; //文件描述符保存在数组当中
public:
    SelectServer(int _p = DFL_PORT):port(_p){}

    void InitServer(){
        //静态方法用类名直接访问
        for(int i = 0; i < NUM; i++){
            fd_array[i] = DFL_FD;
        }
        lsock = Sock::Socket();
        Sock::Setsockopt(lsock);
        Sock::Bind(lsock, port);
        Sock::Listen(lsock);

        //刚开始的时候只有一个listen套接字，将该套接字放入数组当中
        fd_array[0] = lsock;

    }

    void AddFd2Array(int sock){
        int i = 0;
        for(; i < NUM; i++){
            if(fd_array[i] == DFL_FD){
                break;
            }
        }
        if(i >= NUM){
            cerr << "fd array is full, close sock" << endl;
            close(sock);
        }
        else{
            fd_array[i] = sock;
            cout << "fd: " << sock << "add to select..." << endl;
        }
    }

    void DefFdFromArray(int index){
        if(index >= 0 && index < NUM){
            fd_array[index] = DFL_FD;
        }
    }

    void HandlerEvents(fd_set *rfds){
        for(int i = 0; i < NUM; i++){
            if(fd_array[i] == DFL_FD){
                continue;
            }
            
            //和rfds有两种关系，一种是调用rfds前，将数组的有效文件描述符放入rfds中，一种是调用rfds后，检测众多文件描述符当中哪些在，代表就绪
            if(FD_ISSET(fd_array[i], rfds)){
                //read ready
                if(fd_array[i] == lsock){
                    //link event
                    int sock = Sock::Accept(lsock);
                    if(sock >= 0){
                        //sock ok
                        //将获取到的有效文件描述符放入数组当中
                        cout << "get a new link..." << endl;
                        AddFd2Array(sock);
                    }
                }
                else{
                    //对应的文件描述符数据就绪了
                    //data ready event        
                    //bug
                    char buf[10240];
                    ssize_t s = recv(fd_array[i], buf, sizeof(buf), 0);
                    if(s > 0){
                        buf[s] = 0;
                        cout << "client#" << buf << endl;
                    }
                    else if(s == 0){
                        cout << "client quit" << endl;
                        close(fd_array[i]);
                        DefFdFromArray(i);
                    }
                    else{
                        close(fd_array[i]);
                        DefFdFromArray(i);
                    }
                }
            }
        }
    }

    void Start(){
        int maxfd = DFL_FD;
        for(;;){
            //select
            //位图
            fd_set rfds;
            FD_ZERO(&rfds);
            //rfds是一个输入输出型参数，因此每次都需要设定，重新设定需要知道把哪一个文件描述符放入rfds当中，所以用for循环将参数添加进来
            cout << "fd_array: ";
            for(int i = 0; i < NUM; i++){
                if(fd_array[i] != DFL_FD){
                    cout << fd_array[i] << " ";
                    FD_SET(fd_array[i], &rfds);
                    if(maxfd < fd_array[i]){
                        maxfd = fd_array[i];
                    }
                }
            }

            cout << endl;
            printf("begin select...\n");
            struct timeval timeout = {5, 0};

            switch(select(maxfd+1, &rfds, nullptr, nullptr, &timeout)){
                case 0:
                    printf("timeout...\n");
                    break;
                case -1:
                    perror("select error!\n");
                    break;
                dafault:
                    //success
                    HandlerEvents(&rfds);
                    break;
            }
        }
    }

    ~SelectServer(){}
};

