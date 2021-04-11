#include <iostream>
#include <thread>
#include <vector>
#include <future>

int sum(const std::vector<int>& vec, int start, int end)
{
  int sum = 0;
  for (int i = start; i < end; i++)
  {
    sum += vec[i];
  }
  return sum;
}

void MultiplyVector(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& result_vector, int start,
                    int end)
{
  for (int i = start; i < end; i++)
  {
    result_vector[i] = a[i] * b[i];
  }
}

int Task2()
{
  std::vector<int> vector1(1000, 2);
  std::vector<int> vector2(1000, 3);
  std::vector<int> result_vector(1000);

  for (int i = 0; i < 10; i++)
  {
    std::async(MultiplyVector, std::ref(vector1), std::ref(vector2), std::ref(result_vector), i * 100, i * 100 + 100);
  }

  int summary = 0;
  for (int i = 0; i < 10; i++)
  {
    summary += std::async(sum, std::ref(result_vector), i * 100, i * 100 + 100).get();
  }

  std::cout << summary << std::endl;

  return 0;
}
