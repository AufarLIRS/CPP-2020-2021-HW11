#ifndef TASK1_H
#define TASK1_H
#include <thread>
#include <vector>
#include <random>
class Task1
{
private:
public:
  static int getRandomNumber(int min, int max);

  static std::vector<int> v10;
  static void VectorPadding(std::vector<int>& v1000);
  static void GetVectorSum(std::vector<int> v1000, int step = 0, int inc100 = 0);
  static int GetSumv10();
};

#endif  // TASK1_H
