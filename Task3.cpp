#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>
#include <future>

std::condition_variable cv;
bool ready = false;

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
    std::cout << result_vector[i] << std::endl;
  }
}

void go()
{
  cv.notify_all();
}

int Task3()
{
  std::vector<int> vector1(1000, 2);
  std::vector<int> vector2(1000, 3);
  std::vector<int> result_vector(1000);
  std::vector<std::thread> threads(10);
  // spawn 10 threads:
  for (int i = 0; i < 10; ++i)
  {
    threads[i] = std::thread(MultiplyVector, std::ref(vector1), std::ref(vector2), std::ref(result_vector), i * 100,
                             i * 100 + 100);
  }

  go();

  for (auto& th : threads)
    th.join();

  int summary = 0;
  for (int i = 0; i < 10; i++)
  {
    summary += std::async(sum, std::ref(result_vector), i * 100, i * 100 + 100).get();
  }

  std::cout << summary << std::endl;

  return 0;
}
