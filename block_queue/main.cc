#include"BlockQueue.hpp"

using namespace std;

void *consumer_run(void *arg){
    BlockQueue *bq = (BlockQueue*)arg;
    while(true){
        //多c 加lock
        //int n = 0;
        Task t;
        bq->Get(t);
        cout << "consumer: "<< t.x << " + " << t.y << " = " << t.Run() <<endl;;
        //unlock
        //cout << "consumer data is :" << n << endl;
        sleep(2);
    }
}

void *productor_run(void *arg){
    BlockQueue *bq = (BlockQueue*)arg;
    while(true){
        //多p 加lock
        //int data = rand()%10 + 1;
        int x = rand()%10 + 1;
        int y = rand()%100 + 1;


        Task t(x, y);
        bq->Put(t);
        //unlock
        cout << "product Task is :" << x << " + " << y << " = ?" << endl;
    }
}

int main(){
    //不定义为全局，为了给线程传参，传堆上开辟的空间
    BlockQueue *bq = new BlockQueue(5);
    pthread_t c, p;
    //多线程需要解决多c和多p之间的互斥关系
    //第四个参数:传给线程最后启动函数的参数
    pthread_create(&c, nullptr, consumer_run, (void*)bq);
    pthread_create(&p, nullptr, productor_run, (void*)bq);

    pthread_join(c, nullptr);
    pthread_join(p, nullptr);

    delete bq;
    return 0;
}
