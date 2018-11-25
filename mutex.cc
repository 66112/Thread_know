#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

static size_t taticke;
void* handler(void* arg)
{
    int i = (int)arg;
    while(1){
        cout << "i love you " << endl;
        sleep(3);
        pthread_exit((void*)"i am tired");      //返回信息
    }
}

int main()
{ 
    int i=0,num=5;
    for(; i < num; i++){
        pthread_t tid;        
        pthread_create(&tid,NULL,handler,(void*)i);
        pthread_detach(tid);
    }
    void* ret;
   // sleep(5);
   // pthread_cancel(tid);  //取消线程
   // pthread_detach(tid);  //分离线程
   // pthread_join(tid,&ret);
    cout << "thread 1: "<< (char*)ret << endl;  //可以打印出来
}
