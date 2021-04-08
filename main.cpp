#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <numeric>
#include <mutex>
#include <array>
#include <future>
std::mutex mutex;
int saveSumInVector(const std::vector<int>& data, int start, int finish)
{
  int sum = 0;
  for (int i = start; i < finish; i++)
  {
    sum += data[i];
  }
  return sum;
}

void task_1()
{
  std::vector<int> sums(10);
  std::vector<int> vector(1000, 1);
  for (int i = 0; i < 10; i++)
    sums[i] = std::async(saveSumInVector, std::ref(vector), i * 100, (i + 1) * 100).get();
  int sum = std::accumulate(sums.begin(), sums.end(), 0);
  std::cout << "task 1: " << sum << std::endl;
}

void multiplyElementsAndSave(std::vector<int>& savingVector, const std::vector<int>& vect1,
                             const std::vector<int>& vect2, int start, int finish)
{
  for (int i = start; i < finish; i++)
  {
    savingVector[i] = vect1[i] * vect2[i];
  }
}

void task_2()
{
  std::vector<int> v1(1000, 1);
  std::vector<int> v2(1000, 2);
  std::vector<int> multiplyResults(1000);
  std::vector<std::thread> threads;
  std::vector<int> sums(10);
  //сохраняю произведения
  for (int i = 0; i < 10; i++)
  {
    threads.push_back(std::thread(multiplyElementsAndSave, std::ref(multiplyResults), std::ref(v1), std::ref(v2),
                                  i * 100, (i + 1) * 100));
  }
  for (auto& th : threads)
    th.join();

  //Вычисляю суммы разных отрезков произведений в отдельных потоках
  for (int i = 0; i < 10; i++)
  {
    sums[i] = std::async(saveSumInVector, std::ref(multiplyResults), i * 100, (i + 1) * 100).get();
  }
  int sum = std::accumulate(sums.begin(), sums.end(), 0);
  std::cout << "task 2: " << sum << std::endl;
}

std::condition_variable cv;
void multiplyAndSaveSum(std::vector<int>& sumVector, int savingNumber, const std::vector<int>& vect1,
                        const std::vector<int>& vect2, int start, int finish)
{
  int n = finish - start;
  std::vector<int> currentMultiplyResults(n);
  int counter = 0;
  for (int i = start; i < finish; i++)
  {
    currentMultiplyResults[counter] = vect1[i] * vect2[i];
    counter++;
  }
  std::unique_lock<std::mutex> lck(mutex);
  cv.wait(lck);
  int sum = std::accumulate(currentMultiplyResults.begin(), currentMultiplyResults.end(), 0);
  sumVector[savingNumber] = sum;
}

void go()
{
  cv.notify_all();
}

void task_3()
{
  std::vector<int> v1(1000, 1);
  std::vector<int> v2(1000, 2);
  std::vector<int> sums(10);
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; i++)
  {
    threads.push_back(
        std::thread(multiplyAndSaveSum, std::ref(sums), i, std::ref(v1), std::ref(v2), i * 100, (i + 1) * 100));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  go();
  for (auto& th : threads)
    th.join();
  int sum = std::accumulate(sums.begin(), sums.end(), 0);
  std::cout << "task 3: " << sum << std::endl;
}

int main()
{
  task_1();
  task_2();
  task_3();

  return 0;
}
