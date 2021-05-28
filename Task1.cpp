#include <iostream>
#include <numeric>
#include <future>
#include "main.h"

void task_1()
{
  std::vector<int> sums(10);
  std::vector<int> vector(1000, 1);
  for (int i = 0; i < 10; i++)
    sums[i] = std::async(saveSumInVector, std::ref(vector), i * 100, (i + 1) * 100).get();
  int sum = std::accumulate(sums.begin(), sums.end(), 0);
  std::cout << "task 1: " << sum << std::endl;
}
