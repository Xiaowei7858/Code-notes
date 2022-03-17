#pragma once

#include<iostream>
#include<queue>
#include<map>
#include<string>
#include<math.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>

#define NUM 5 

class Task{
public:
    //int base;
    int sock;
    std::map<std::string, std::string> dict;
public:
    Task(){}
    Task(int _sock):sock(_sock){
        dict.insert(std::make_pair<std::string, std::string>("apple", "苹果"));
    }

    void Run(){
        char buffer[64];
        std::cout << "task is running " << std::endl;
        size_t s = recv(sock, buffer, sizeof(buffer)-1, 0);
        if(s > 0){
            buffer[s] = 0;
            std::string key = buffer;

            send(sock, dict[key].c_str(), dict[key].size(), 0);
        }
        if(s == 0){
            std::cout << "client quit ... " << std::endl;
        }
        else{
            std::cout << "recv client data error ... " << std::endl; //std::cout << "thread is [" << pthread_self() << "]task run ... done: base# " << base << "pow is #" << pow(base, 2) << std::endl; //std::cout << "task is running" << std::endl;
    }

    ~Task(){
        std::cout << "server close sock :" << sock << std::endl;
        close(sock);
    }

};

class ThreadPool{
private:
    std::queue<Task*> q; //Task*
    int max_num;
    pthread_mutex_t lock;
    pthread_cond_t cond; //only consumer, thread pool thread;
    //bool quit;
public:
    void LockQueue(){
        pthread_mutex_lock(&lock);
    }

    void UnLockQueue(){
        pthread_mutex_unlock(&lock);
    }

    bool IsEmpty(){
        return q.size() == 0;
    }

    void Threadwait(){
        pthread_cond_wait(&cond, &lock);
    }

    void ThreadWakeup(){
        //if(low_water > 30){
        //    //pthread_cond_broadcast(&cond);
        //}
        pthread_cond_signal(&cond);
        //pthread_cond_broadcast(&cond);
    }

    void ThreadsWakeup(){
        pthread_cond_broadcast(&cond);
    }
public:
    ThreadPool(int _max=NUM):max_num(_max){}// quit(false){

    //只需要一个参数，除去this指针
    //加static，表示该方法只属于类，不属于对象
    //static方法只能访问static方法，因为没有this指针，找不到属于该对象的方法
    static void *Routine(void *arg){
        ThreadPool *this_p = (ThreadPool*)arg;
        while(true){
            this_p->LockQueue();
            //防止拿取失败，所以不用if
            while(this_p->IsEmpty()){
                this_p->Threadwait();
            }

            Task *t;
            this_p->Get(&t);
            this_p->UnLockQueue();
            t->Run();
            delete t;
        }
    }
    void ThreadPoolInit(){
        pthread_mutex_init(&lock, nullptr);
        pthread_cond_init(&cond, nullptr);

        pthread_t t;
        for(int i = 0; i < max_num; i++){
            //传入this
            pthread_create(&t, nullptr, Routine, this);
        }
    }
    
    //server
    void Put(Task &in){
        LockQueue();
        q.push(&in);
        UnLockQueue();

        ThreadWakeup();
    }

    //Thread pool t; 拷贝的形式拿出来的需要修改
    void Get(Task **out){
        Task *t = q.front();
        q.pop();
        *out = t;
    }

    void ThreadQuit(){
        //if(!IsEmpty()){
        //    std::cout << "task queue is not empty()" << std::endl;
        //    return;
        //}
        //quit = true;
        //ThreadsWakeup();
    }

    ~ThreadPool(){
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);
    }

};
