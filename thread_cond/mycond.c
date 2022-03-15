#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;

void *routine_r1(void *arg){
    const char *name = (char*)arg;

    while(1){
        pthread_cond_wait(&cond, &lock);
        printf("get cond, %s 活动...\n", name);
    }
}
void *routine_r2(void *arg){
    const char *name = (char*)arg;

    while(1){
        sleep(rand()%3 + 1);
        pthread_cond_signal(&cond);
        printf("%s signal done ... \n", name);
    }
}

int main(){
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, routine_r1, "thread1");
    pthread_create(&t2, NULL, routine_r2, "thread2");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}

