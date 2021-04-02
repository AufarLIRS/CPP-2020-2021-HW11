#include <iostream>
#include <vector>
#include <future>

struct sum2;

void sum3(const std::vector<int>& data, const int step, const int n, int& sum);

void task_1_0();

void task_2_0();

void task_1()
{
  constexpr int thread_n = 10;
  // data_n must be integrally dividable by thread_n
  constexpr int data_n = 1000;
  constexpr int step = data_n / thread_n;
  const std::vector<int> data(data_n, 3);
  int answer = 0;
  std::vector<std::pair<int, std::thread>> sums(thread_n);
  for (int i = 0; i < thread_n; i++)
  {
    sums[i].first = 0;
    sums[i].second = std::thread(
        [&sums](const std::vector<int>& data, const int n, const int step) {
          for (int j = step * n; j < step * (n + 1); j++)
          {
            sums[n].first += data[j];
          }
        },
        std::ref(data), i, step);
  }
  for (int i = 0; i < thread_n; i++)
  {
    sums[i].second.join();
    answer += sums[i].first;
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
  std::vector<int> vector_result(vector_size, 0);
  std::vector<std::pair<int, std::thread>> thread_pool(thread_n);
  constexpr int step = vector_size / thread_n;
  std::mutex mutex;
  std::condition_variable cv;
  std::atomic<int> counter(0);
  for (int i = 0; i < thread_n; i++)
  {
    thread_pool[i].first = 0;
    thread_pool[i].second = std::thread(
        [&vector_result, &thread_pool, &cv, &mutex,
         &counter](const std::vector<int>& vec1, const std::vector<int>& vec2, const int n, const int step) {
          for (int j = step * n; j < step * (n + 1); j++)
          {
            vector_result[j] = vec1[j] * vec2[j];
          }
          std::unique_lock<std::mutex> lock(mutex);
          counter++;
          cv.notify_all();
          cv.wait(lock, [&counter] { return counter == thread_n; });
          for (int j = step * n; j < step * (n + 1); j++)
          {
            thread_pool[n].first += vector_result[j];
          }
        },
        std::ref(vector1), std::ref(vector2), i, step);
  }
  int answer = 0;
  for (int i = 0; i < thread_n; i++)
  {
    thread_pool[i].second.join();
    answer += thread_pool[i].first;
  }
  std::cout << answer << std::endl;
}

int main()
{
  task_1();
  task_2();

  return 0;
}

struct sum2
{
  void operator()(const std::vector<int>& data, const int step, const int n, int& sum)
  {
    for (int i = step * n; i < step * (n + 1); i++)
    {
      sum += data[i];
    }
  }
};

void sum3(const std::vector<int>& data, const int step, const int n, int& sum)
{
  for (int i = step * n; i < step * (n + 1); i++)
  {
    sum += data[i];
  }
}

void task_1_0()
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
        std::launch::async,
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

void task_2_0()
{
  constexpr int thread_n = 10;
  // vector_size must be integrally dividable by thread_n
  constexpr int vector_size = 1000;
  const std::vector<int> vector1(vector_size, 2);
  const std::vector<int> vector2(vector_size, 3);
  // vector_result not necessary should be atomic because
  // we accessing any element only one time
  std::vector<int> vector_result(vector_size, 0);
  std::vector<std::future<int>> thread_pool(thread_n);
  constexpr int step = vector_size / thread_n;
  std::mutex mutex;
  std::condition_variable cv;
  std::atomic<int> counter(0);
  for (int i = 0; i < thread_n; i++)
  {
    thread_pool[i] = std::async(
        std::launch::async,
        [&vector_result, &cv, &mutex, &counter](const std::vector<int>& vec1, const std::vector<int>& vec2, const int n,
                                                const int step) {
          int sum = 0;
          for (int j = step * n; j < step * (n + 1); j++)
          {
            vector_result[j] = vec1[j] * vec2[j];
          }
          std::unique_lock<std::mutex> lock(mutex);
          counter++;
          cv.notify_all();
          cv.wait(lock, [&counter] { return counter == thread_n; });
          for (int j = step * n; j < step * (n + 1); j++)
          {
            sum += vector_result[j];
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
