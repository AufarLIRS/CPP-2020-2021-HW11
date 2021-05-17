#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>
#include <future>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void MultiplyAndSumVector(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& result_vector,
                          int& sum, int start, int end)
{
  std::unique_lock<std::mutex> lck(mtx);
  for (int i = start; i < end; i++)
  {
    result_vector[i] = a[i] * b[i];
    std::cout << result_vector[i] << std::endl;
  }
  if (start == 900)
  {
    ready = true;
  }

  cv.wait(lck);

  for (int i = start; i < end; i++)
  {
    sum += result_vector[i];
    std::cout << sum << std::endl;
  }
}

int Task3()
{
  std::vector<int> vector1(1000, 2);
  std::vector<int> vector2(1000, 3);
  std::vector<int> result_vector(1000);
  std::vector<std::thread> threads(10);
  int summary = 0;
  // spawn 10 threads:
  for (int i = 0; i < 10; ++i)
  {
    threads[i] = std::thread(MultiplyAndSumVector, std::ref(vector1), std::ref(vector2), std::ref(result_vector),
                             std::ref(summary), i * 100, i * 100 + 100);
  }

  while (true)
  {
    if (ready)
    {
      cv.notify_all();
      cv.notify_one();  // for last thread
      break;
    }
  }

  for (auto& th : threads)
    th.join();

  std::cout << summary << std::endl;

  return 0;
}
