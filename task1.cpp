#include "task1.h"
#include <time.h>
#include <chrono>
std::vector<int> Task1::v10(10);

void Task1::GetVectorSum(std::vector<int> v1000, int step, int inc100)
{
  for (int i = 0 + inc100; i < 100 + inc100; i++)
  {
    v10[step] += v1000[i];
  }
}
void Task1::VectorFlooding(std::vector<int>& v1000)
{
  for (int i = 0; i < 1000; i++)
  {
    std::chrono::time_point<std::chrono::steady_clock> tp = std::chrono::steady_clock::now();
    v1000.push_back(
        getRandomNumber(0, std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count() % 100));
  }
}
int Task1::getRandomNumber(int min, int max)
{
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
int Task1::GetSumv10()
{
  int sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sum += v10[i];
  }
  return sum;
}
