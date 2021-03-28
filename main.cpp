#include "Task1.h"
#include "Task2.h"

int main()
{
  // TASK 1
  /**************************************************************************************/
  std::cout << "Task 1" << std::endl;
  auto vectorPartSums = Start1(1000);  // example of vector 1000 elements
  int sum_of_elems = 0;
  for (auto& n : vectorPartSums)
    sum_of_elems += n;

  std::cout << "Sum of partial sums of vector elements = " << sum_of_elems << std::endl;
  std::cout << std::endl;
  /**************************************************************************************/

  // TASK 2
  /**************************************************************************************/
  std::cout << "Task 2" << std::endl;
  auto vectorElemsProduct = Start2(1000);
  sum_of_elems = 0;
  for (auto& n : vectorElemsProduct)
    sum_of_elems += n;
  std::cout << "Scalar product of two vectors = " << sum_of_elems << std::endl;
  std::cout << std::endl;
  /**************************************************************************************/

  return 0;
}
