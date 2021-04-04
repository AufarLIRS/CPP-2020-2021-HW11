#ifndef TASK2_H
#define TASK2_H
#include "task1.h"
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <numeric>
#include <iostream>
#include <condition_variable>
class task2 : public Task1
{
  static int getRandomNumber(int min, int max);

public:
  static std::condition_variable cv;
  static std::vector<int> v10;
  static std::mutex mtx;
  static void VectorPaddings(std::vector<int>& a1000, std::vector<int>& b1000);
  static void GetScalarProduct(std::vector<int> a, std::vector<int> b, int step = 0, int inc100 = 0);
  static int GetSumv10();
  static void go();
};

#endif  // TASK2_H
