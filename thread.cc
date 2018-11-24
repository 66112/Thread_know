#include <iostream>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
using namespace std;

void* thread_my(void* arg)
{
    pid_t _tid1;
    _tid1 = syscall(SYS_gettid);
    const char* thread_name = (const char*)arg;
    while(1){
        cout << "thread_my: " << _tid1 << endl;
        cout << thread_name << " running... "<< getpid() << " tid: "<< pthread_self()<<endl;
        sleep(1);
	    pthread_exit(arg);
    }
}

int main()
{
    pthread_t tid;    //用户态tid,是一个虚拟地址
    pid_t _tid;           //内核态tid,是一个线程的标识符
    _tid = syscall(SYS_gettid);   //内核调度要用

    //创建一个线程，参数(输出型参数(把tid填成新线程的用户态线程地址),NULL表示线程的默认属性，线程启动后要执行的函数，线程启动后要执行的参数)
    pthread_create(&tid,NULL,thread_my,(void*)"thread 1"); 
	void* ret;
	//ret为输出型参数，
	pthread_join(tid,&ret);
	cout << "thread 1 quit,code is: "<< (int)ret <<endl;
  //  while(1){
  //      cout << "main tid: "<< _tid <<endl;
  //      //getpid()返回的是线程组（进程）的pid,也是主线程的tgid; 
  //      //pthread_self()返回的是当前线程的用户态id,也就是地址空间的地址
  //      cout << "main thread run... " << getpid() << " tid: " << pthread_self() << endl; 
  //      sleep(1);
  //  }
}
