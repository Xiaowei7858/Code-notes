#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thread_run(void *arg){
    while(1){
        printf("i am %s, pid:%d \n", (char*)arg, getpid());
        sleep(1);
    }
}

int main(){
    pthread_t tid;
    pthread_create(&tid, NULL, thread_run, (void*)"thread 1");

    while(1){
        printf("i am main pthread! pid:%d \n", getpid());
        sleep(2);
    }
}
