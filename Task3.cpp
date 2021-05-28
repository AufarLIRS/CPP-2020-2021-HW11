#include <iostream>
#include <vector>
#include <numeric>
#include <mutex>
#include <array>
#include <future>
std::mutex mutex;

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
