#include <iostream>
#include <vector>
#include <future>

void task_1();

void task_2();

int main()
{
  task_1();
  task_2();

  return 0;
}

void task_1()
{
  constexpr int thread_n = 10;
  // data_n must be integrally dividable by thread_n
  constexpr int data_n = 1000;
  constexpr int step = data_n / thread_n;
  const std::vector<int> data(data_n, 3);
  int answer = 0;
  std::vector<std::future<int>> sums(thread_n);
  for (int i = 0; i < thread_n; i++)
  {
    sums[i] = std::async(
        [](const std::vector<int>& data, const int n) {
          int sum = 0;
          for (int i = step * n; i < step * (n + 1); i++)
          {
            sum += data[i];
          }
          return sum;
        },
        std::ref(data), i);
  }
  for (int i = 0; i < thread_n; i++)
  {
    answer += sums[i].get();
  }
  std::cout << answer << std::endl;
}

void task_2()
{
  constexpr int thread_n = 10;
  // vector_size must be integrally dividable by thread_n
  constexpr int vector_size = 1000;
  const std::vector<int> vector1(vector_size, 2);
  const std::vector<int> vector2(vector_size, 3);
  std::vector<std::future<int>> thread_pool(thread_n);
  constexpr int step = vector_size / thread_n;
  for (int i = 0; i < thread_n; i++)
  {
    thread_pool[i] = std::async(
        [](const std::vector<int>& vec1, const std::vector<int>& vec2, const int n, const int step) {
          int sum = 0;
          for (int j = step * n; j < step * (n + 1); j++)
          {
            sum += vec1[j] * vec2[j];
          }
          return sum;
        },
        std::ref(vector1), std::ref(vector2), i, step);
  }
  int answer = 0;
  for (int i = 0; i < thread_n; i++)
  {
    answer += thread_pool[i].get();
  }
  std::cout << answer << std::endl;
}
