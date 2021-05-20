#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>

class MyThread: public QThread
{

public:
    std::vector<int>::iterator arr;
    int num;

    int sum =0;
    explicit MyThread();
    void run();
};

#endif // MYTHREAD_H
