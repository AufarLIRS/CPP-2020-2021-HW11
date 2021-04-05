#include "Task1.h"

std::vector<int> vectorPartSums(10);  //общий вектор частичных сумм потоков

int sumVectElems(std::vector<int>& initialVector, int start, int end, int thread_number)
{
  int partial_sum = 0;
  for (int i = start; i < end; i++)
  {
    partial_sum += initialVector[i];
  }
  std::cout << "Thread #" << thread_number << " wants to push it's sum to the general vector" << std::endl;
  std::cout << "Thread #" << thread_number << " has ended to work" << std::endl;
  return partial_sum;
}

std::vector<int> Start1(int vectorLength)
{
  std::vector<int> large_vector(vectorLength, 1);
  std::vector<std::future<int>> partial_async_sums_vector;

  int step = vectorLength / 10;
  int start = 0;
  int end = step;

  for (int i = 0; i < 10; i++)
  {
    partial_async_sums_vector.push_back(
        std::async(std::launch::deferred, sumVectElems, std::ref(large_vector), start, end, i));
    start += step;
    end += step;
    std::cout << "Thread #" << i << " is deferred" << std::endl;
  }

  for (auto& th : partial_async_sums_vector)
  {
    vectorPartSums.push_back(th.get());
  }

  return vectorPartSums;
}
