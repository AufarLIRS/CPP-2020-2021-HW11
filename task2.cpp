#include "task2.h"
std::vector<int> task2::v10(10);
std::condition_variable task2::cv;
std::mutex task2::mtx;

void task2::GetScalarProduct(std::vector<int> a, std::vector<int> b, int step, int inc100)
{
  std::unique_lock<std::mutex> lck(mtx);
  for (int i = 0 + inc100; i < 100 + inc100; i++)
  {
    v10[step] += a[i] * b[i];
  }
  cv.wait(lck);
}
int task2::getRandomNumber(int min, int max)
{
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void task2::VectorPaddings(std::vector<int>& a1000, std::vector<int>& b1000)
{
  for (int i = 0; i < 1000; i++)
  {
    std::chrono::time_point<std::chrono::steady_clock> tp = std::chrono::steady_clock::now();
    a1000.push_back(
        getRandomNumber(0, std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count() % 100));
    tp = std::chrono::steady_clock::now();
    b1000.push_back(
        getRandomNumber(0, std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count() % 100));
  }
}
int task2::GetSumv10()
{
  int sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sum += v10[i];
  }
  return sum;
}
void task2::go()
{
  cv.notify_all();
}
