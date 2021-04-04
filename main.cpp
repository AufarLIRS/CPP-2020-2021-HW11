#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <numeric>
#include <mutex>
#include <array>
#include <future>
std::mutex mutex;
void saveSumInVector(std::vector<int>& sums, std::vector<int>& data, int start, int finish)
{
  int sum = 0;
  for (int i = start; i < finish; i++)
  {
    sum += data[i];
  }
  std::lock_guard<std::mutex> guard(mutex);
  sums.push_back(sum);
}

void task_1()
{
  std::vector<int> sums;
  std::vector<int> vector(1000, 1);
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; i++)
    threads.push_back(std::thread(saveSumInVector, std::ref(sums), std::ref(vector), i * 100, (i + 1) * 100));
  for (auto& th : threads)
    th.join();
  int sum = std::accumulate(sums.begin(), sums.end(), 0);
  std::cout << "task 1: " << sum << std::endl;
}

void multiplyElements(std::vector<int>& result, std::vector<int>& vect1, std::vector<int>& vect2, int start, int finish)
{
  for (int i = start; i < finish; i++)
  {
    result[i] = vect1[i] * vect2[i];
  }
}

int sum(std::vector<int>& data, int start, int finish)
{
  int result = 0;
  for (int i = start; i < finish; i++)
  {
    result += data[i];
  }
  return result;
}

void task_2()
{
  std::vector<int> v1(1000, 1);
  std::vector<int> v2(1000, 2);
  std::vector<int> multiplyResults;
  std::vector<std::thread> threads;
  //сохраняю произведения
  for (int i = 0; i < 10; i++)
  {
    threads.push_back(
        std::thread(multiplyElements, std::ref(multiplyResults), std::ref(v1), std::ref(v2), i * 100, (i + 1) * 100));
  }
  for (auto& th : threads)
    th.join();

  std::vector<std::future<int>> sums;
  //Вычисляю суммы разных отрезков произведений в отдельных потоках
  for (int i = 0; i < 10; i++)
  {
    sums[i] = std::async(sum, std::ref(multiplyResults), i * 100, (i + 1) * 100);
  }
  int sum = 0;

  //Вычисляю сумму
  for (int i = 0; i < 10; i++)
  {
    sum += sums[i].get();
  }

  std::cout << "task 2: " << sum << std::endl;
}

std::condition_variable cv;
int multiplyAndGetSum(std::vector<int>& vect1, std::vector<int>& vect2, int start, int finish)
{
  std::vector<int> sums;
  for (int i = start; i < finish; i++)
  {
    sums[i] = vect1[i] * vect2[i];
  }
  std::unique_lock<std::mutex> lck(mutex);
  cv.wait(lck);
  int result = 0;
  for (int i = start; i < finish; i++)
  {
    result += sums[i];
  }
  return result;
}

void go()
{
  cv.notify_all();
}

void task_3()
{
  std::vector<int> v1(1000, 1);
  std::vector<int> v2(1000, 2);
  std::vector<std::future<int>> sums;
  for (int i = 0; i < 10; ++i)
  {
    sums[i] = std::async(multiplyAndGetSum, std::ref(v1), std::ref(v2), i * 100, (i + 1) * 100);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  go();
  int sum = 0;
  for (int i = 0; i < 10; i++)
    sum += sums[i].get();
  std::cout << "task 3: " << sum << std::endl;
}

int main()
{
  // task_1();
  // task_2();
  task_3();

  return 0;
}
