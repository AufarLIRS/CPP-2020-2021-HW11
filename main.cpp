#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>
#include "Task1.h"

int main()
{
  // TASK 1
  /**************************************************************************************/
  auto vectorPartSums = Start(1000);
  int sum_of_elems = 0;
  for (auto& n : vectorPartSums)
    sum_of_elems += n;

  std::cout << "Sum of partial sums of vector elements = " << sum_of_elems << std::endl;
  /**************************************************************************************/

  return 0;
}
