#include <iostream>
#include <numeric>
#include <future>
#include "main.h"


void task_2()
{
  std::vector<int> v1(1000, 1);
  std::vector<int> v2(1000, 2);
  std::vector<int> multiplyResults(1000);
  std::vector<std::thread> threads;
  std::vector<int> sums(10);

  for (int i = 0; i < 10; i++)
  {
    threads.push_back(std::thread(multiplyElementsAndSave, std::ref(multiplyResults), std::ref(v1), std::ref(v2),
                                  i * 100, (i + 1) * 100));
  }
  for (auto& th : threads)
    th.join();

  for (int i = 0; i < 10; i++)
  {
    sums[i] = std::async(saveSumInVector, std::ref(multiplyResults), i * 100, (i + 1) * 100).get();
  }
  int sum = std::accumulate(sums.begin(), sums.end(), 0);
  std::cout << "task 2: " << sum << std::endl;
}

