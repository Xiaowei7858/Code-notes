#include "Sock.hpp"

#define SIZE 64
class bucket {
public:
    char buffer[10240]; //request
    int pos;
    int fd;
    bucket(int sock):fd(sock), pos(0){
        memset(buffer, 0, sizeof(buffer));
    }
    ~bucket(){}
};

class EpollServer{
private:
    int lsock;
    int port;
    int epfd;
public:
    EpollServer(int _p = 8081):port(_p){}

    void AddEvent2Epoll(int sock, uint32_t event){
        struct epoll_event ev;
        ev.events = event;
        if(sock == lsock){
            ev.data.ptr = nullptr;
        }
        else{
            ev.data.ptr = new bucket(sock);
        }
        epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev);
    }

    void DelEventFromEpoll(int sock){
        close(sock);
        epoll_ctl(epfd, EPOLL_CTL_DEL, sock, nullptr);
    }

    void InitServer(){
        lsock = Sock::Socket();
        Sock::Setsockopt(lsock);
        Sock::Bind(lsock, port);
        Sock::Listen(lsock);

        if(epfd < 0){
            cerr << "epoll_create error" << endl;
            exit(5);
        }
        cout << "listen sock:" << lsock << endl;
        cout << "epoll fd:" << epfd << endl; 
    }

    void HandlerEvents(struct epoll_event revs[], int num){
        for(int i = 0; i < num; i++){
            uint32_t ev = revs[i].events;
            if(ev & EPOLLIN){
                if(revs[i].data.ptr != nullptr){
                    bucket *bp = (bucket*)revs[i].data.ptr;
                    ssize_t s = recv(bp->fd, bp->buffer+bp->pos, sizeof(bp->buffer)-bp->pos, 0);
                    if(s > 0){
                        bp->pos += s;
                        cout << "client #" << bp->buffer << endl;
                        if(bp->pos >= sizeof(bp->buffer)){
                            struct epoll_event temp;
                            temp.events = EPOLLOUT;
                            temp.data.ptr = bp;
                            epoll_ctl(epfd, EPOLL_CTL_MOD, bp->fd, &temp);
                        }
                    }
                    else if(s == 0){
                        DelEventFromEpoll(bp->fd){
                        delete bp;
                    }
                    else{
                        //TODO
                    }
                }
                else{
                    //listen sock;
                    int sock = Sock::Accept(lsock);
                    if(sock > 0){
                        AddEvent2Epoll(sock, EPOLLIN);
                    }
                }
            }
            else if(ev & EPOLLOUT){
                //write;
                bucket *bp = (bucket*)revs[i].data.ptr;
                //student done
                send(bp->fd, bp->buffer, sizeof(bp->buffer), 0);
                DelEventFromEpoll(bp->fd);
                delete bp;
            }
            else{
                //other events;
            }
        }
    }

    void Start(){
        AddEvent2Epoll(lsock, EPOLLIN);
        int timeout = 1000;
        struct epoll_event revs[SIZE];
        for(;;){
            int num = epoll_wait(epfd, revs, SIZE, timeout);
            switch(num){
                case 0:
                    cout << "time out" << endl;
                    break;
                case -1:
                    cerr << "epoll_wait error" << endl;
                default:
                    HandlerEvents(revs, num);
                    break;
            }
        }
    }

    ~EpollServer(){
        //文件描述符
        close(lsock);
        close(epfd);
    }
};

