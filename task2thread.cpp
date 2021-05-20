#include "task2thread.h"

Task2Thread::Task2Thread()
{

}

void Task2Thread::run(){
    for(int i =0;i<num;++i){
        vec->push_back(arr1[i]*arr2[i]);
        sum++;
    }
}
