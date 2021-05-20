#ifndef TASK2THREAD_H
#define TASK2THREAD_H
#include <QThread>

class Task2Thread : public QThread
{

public:
    std::vector<int>::iterator arr1;
    std::vector<int>::iterator arr2;
    std::vector<int> *vec;
    int num;

    int sum =0;
    explicit Task2Thread();
    void run();
};


#endif // TASK2THREAD_H
