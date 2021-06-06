#include "task1.h"
#include "task2.h"
#include <condition_variable>
#include <iostream>

std::mutex mutex3;
std::condition_variable conditionVar;
std::vector<int> PartProductsOfVectors;
std::vector<int> PartSums(10);

void ScalarProductVectors(std::vector<int>& vec1, std::vector<int>& vec2, int start, int end, int thread_number)
{
  std::unique_lock<std::mutex> uniqueLck(mutex3);
  int product;
  for (int i = start; i < end; i++)
  {
    product = vec1[i] * vec2[i];
    PartProductsOfVectors.insert(PartProductsOfVectors.begin() + i, product);
  }
  std::cout << "Thread " << thread_number << " is waiting." << std::endl;

  conditionVar.wait(uniqueLck);
  std::cout << "Thread " << thread_number << " is continuing his work after waiting." << std::endl;

  int sum = 0;
  for (int i = start; i < end; i++)
  {
    sum += PartProductsOfVectors[i];
  }

  PartSums.insert(PartSums.begin() + thread_number, sum);
  std::cout << "Thread " << thread_number << " finished work." << std::endl;
}

void Go()
{
  conditionVar.notify_all();
}

int main()
{
  std::cout << "Task 1" << std::endl;
  auto vectorPartSums = Start1(1000);
  int sum_of_elems = 0;
  for (auto& n : vectorPartSums)
    sum_of_elems += n;

  std::cout << "Sum = " << sum_of_elems << std::endl;
  std::cout << std::endl;


  std::cout << "Task 2" << std::endl;
  auto vectorElemsProduct = Start2(1000);
  sum_of_elems = 0;
  for (auto& n : vectorElemsProduct)
    sum_of_elems += n;
  std::cout << "Scalar = " << sum_of_elems << std::endl;
  std::cout << std::endl;
}
