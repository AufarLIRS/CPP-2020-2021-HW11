#include "task1.h"

std::vector<int> vectorPartSums(10);

int sumVectElems(std::vector<int>& initialVector, int start, int end, int thread_num)
{
    int part_sum = 0;
    for (int i = start; i < end; i++)
    {
        part_sum += initialVector[i];
    }
    std::cout << "Thread " << thread_num << " wants to push his sum to the general vector." << std::endl;
    std::cout << "Thread " << thread_num << " finished work." << std::endl;
    return part_sum;
}

std::vector<int> Start1(int vectorLength)
{
    std::vector<int> large_vector(vectorLength, 1);
    std::vector<std::future<int>> part_async_sums_vector;
    int step = vectorLength / 10;
    int start = 0;
    int end = step;
    for (int i = 0; i < 10; i++)
    {
        part_async_sums_vector.push_back(std::async(std::launch::deferred, sumVectElems, std::ref(large_vector), start, end, i));
        start += step;
        end += step;
        std::cout << "Thread " << i << " is deferred" << std::endl;
    }
    for (auto& th : part_async_sums_vector)
    {
        vectorPartSums.push_back(th.get());
    }

    return vectorPartSums;
}
