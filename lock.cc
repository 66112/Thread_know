#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <vector>
using namespace std;
pthread_mutex_t lock;

static int tickets=100;
struct attr 
{
    int nummber;         //线程序号
    pthread_t tid;       //线程tid
};

void* Buy_Ticket(void* arg) 
{
    //cout << "i will detach!"<<endl;
    // pthread_detach(pthread_self());
    int number = (int)arg + 1;
    while(1)
    {
        usleep(1000);           //一个线程抢完后，歇歇
        pthread_mutex_lock(&lock);  //加锁
        if(tickets > 0){
            usleep(5000);
            cout << "thread: "<<number << " get a ticket: "<< tickets <<endl;
            tickets--;
            pthread_mutex_unlock(&lock);  //解锁
        }
        else{
            pthread_mutex_unlock(&lock);
            break;
        }
    }
    return (void*)number;
}

int main()
{
    int num = 5;
    vector <attr> thread_list(num);
    pthread_mutex_init(&lock,NULL);   //初始化锁
    for(int i=0;i<num;i++)
    {
       if(0 == pthread_create(&thread_list[i].tid, NULL, Buy_Ticket,(void*)i))
       {
            cout << "create success!"<<endl;    
       }
       if(0 == pthread_detach(thread_list[i].tid))
       {
           cout << "detach success!"<<endl;
       }
    }

    void* ret;
    //for(int i=0;i<num;i++)
    //{
    //    pthread_join(thread_list[i].tid,&ret);
    //    cout << "thread number " << (int)ret << endl;
    //}
    sleep(1);           //等别的线程跑完，主线程才能退出
    pthread_mutex_destroy(&lock);  //销毁锁
    cout<<"end"<<endl;
    return 0;
}
