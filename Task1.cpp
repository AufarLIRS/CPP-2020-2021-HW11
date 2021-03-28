#include "Task1.h"

std::mutex mutex1;
std::vector<int> vecPartSums(10);  //общий вектор частичных сумм потоков

void sumVectElems(std::vector<int>& vec, int start, int end, int i)
{
  std::lock_guard<std::mutex> guard(mutex1);
  int sum = 0;
  for (int i = start; i < end; i++)
  {
    sum += vec[i];
  }
  std::cout << "Thread #" << i << " wants to push it's sum to the general vector" << std::endl;
  vecPartSums.push_back(sum);
  std::cout << "Thread #" << i << " has ended to work" << std::endl;
}

std::vector<int> Start1(int vectorLength)
{
  std::vector<int> large_vector(vectorLength, 1);

  std::array<std::thread, 10> threads;

  int step = vectorLength / 10;
  int start = 0;
  int end = step;

  for (int i = 0; i < 10; i++)
  {
    threads[i] = std::thread(sumVectElems, std::ref(large_vector), start, end, i);
    start += step;
    end += step;
  }

  for (auto& th : threads)
    th.join();

  return vecPartSums;
}
