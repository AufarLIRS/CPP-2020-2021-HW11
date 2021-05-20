#include "mythread.h"

MyThread::MyThread()
{
}


void MyThread::run(){
    for(int i =0;i<num;++i){
        this->sum += arr[i];
    }
}
