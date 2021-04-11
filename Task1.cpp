#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <sstream>

int sum(const std::vector<int>& vec, int start, int end)
{
  int sum = 0;
  for (int i = start; i < end; i++)
  {
    sum += vec[i];
  }
  return sum;
}

int Task1()
{
  std::vector<int> large_array(1000, 1);
  std::vector<int> sums(10);

  for (int i = 0; i < 10; i++)
  {
    sums[i] = std::async(sum, std::ref(large_array), i * 100, i * 100 + 100).get();
  }

  int Summary = std::async(sum, std::ref(sums), 0, 10).get();

  std::cout << Summary << std::endl;

  return 0;
}
