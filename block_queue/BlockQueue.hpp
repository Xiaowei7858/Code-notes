#ifndef __QUEUE_BLOCK_H__
#define __QUEUE_BLOCK_H__

#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<queue>

class Task{
public:
    int x;
    int y;
public:
    Task(int _x, int _y):x(_x), y(_y){}
    Task(){}

    int Run(){
        return x + y;
    }
    ~Task(){}
};

class BlockQueue{
private:
    std::queue<Task> q;
    size_t cap;
    pthread_mutex_t lock;
    pthread_cond_t c_cond; //将来消费者在该条件下等
    pthread_cond_t p_cond; //将来生产者在该条件下等
public:
    bool IsFull(){
        return q.size() >= cap;
    }

    bool IsEmpty(){
        return q.empty();
    }

    void LockQueue(){
        pthread_mutex_lock(&lock);
    }

    void UnLockQueue(){
        pthread_mutex_unlock(&lock);
    }

    void WakeUpComsumer(){
        std::cout << "wake up consumer ... " << std::endl;
        pthread_cond_signal(&c_cond);
    }

    void WakeUpProductor(){
        std::cout << "wake up productor ... " << std::endl;
        pthread_cond_signal(&p_cond);
    }


    void ComsumerWait(){
        std::cout << "comsumer wait ... " << std::endl;
        pthread_cond_wait(&c_cond, &lock);
    }

    void ProductorWait(){
        std::cout << "productor wait ... " << std::endl;
        pthread_cond_wait(&p_cond, &lock);
    }

public:
    BlockQueue(size_t _cap):cap(_cap){
        pthread_mutex_init(&lock, nullptr);
        pthread_cond_init(&c_cond, nullptr);
        pthread_cond_init(&p_cond, nullptr);
    }

    void Put(Task t){
        LockQueue();
        while(IsFull()){ //bug!
            WakeUpComsumer();
            //程序调用失败
            ProductorWait();
        }
        q.push(t);
        UnLockQueue();
    }

    void Get(Task &t){
        LockQueue();
        while(IsEmpty()){
            WakeUpProductor();
            ComsumerWait();
        }
        t = q.front();
        q.pop();
        UnLockQueue();
    }

    ~BlockQueue(){
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&c_cond);
        pthread_cond_destroy(&p_cond);
    }
};



#endif
