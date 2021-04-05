#include "Task1.h"
#include "Task2.h"
#include <condition_variable>

std::mutex mutex3;
std::condition_variable conditionVar;
std::vector<int> PartProductsOfVectors;  //общий вектор произведений элементов векторов
std::vector<int> PartSums(10);

void ScalarProductVectors(std::vector<int>& vec1, std::vector<int>& vec2, int start, int end, int i)
{
  std::unique_lock<std::mutex> uniqueLck(mutex3);
  int product;
  for (int i = start; i < end; i++)
  {
    product = vec1[i] * vec2[i];
    PartProductsOfVectors.insert(PartProductsOfVectors.begin() + i, product);
  }
  std::cout << "Thread #" << i << " is waiting" << std::endl;

  conditionVar.wait(uniqueLck);
  std::cout << "Thread #" << i << " is continuing to work after waiting" << std::endl;

  int sum = 0;
  for (int i = start; i < end; i++)
  {
    sum += PartProductsOfVectors[i];
  }

  PartSums.insert(PartSums.begin() + i, sum);
  std::cout << "Thread #" << i << " has ended to work" << std::endl;
}

void Go()
{
  conditionVar.notify_all();
}

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

  // TASK 3
  /**************************************************************************************/
  std::cout << "Task 3" << std::endl;
  std::vector<int> vec1(1000, 3);
  std::vector<int> vec2(1000, 5);

  std::array<std::thread, 10> threads;

  int step = 100;
  int start = 0;
  int end = step;

  for (int i = 0; i < 10; i++)
  {
    threads[i] = std::thread(ScalarProductVectors, std::ref(vec1), std::ref(vec2), start, end, i);
    start += step;
    end += step;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  Go();

  for (auto& th : threads)
    th.join();

  sum_of_elems = 0;
  for (auto& n : PartSums)
    sum_of_elems += n;
  std::cout << "Scalar product of two vectors = " << sum_of_elems << std::endl;
  std::cout << std::endl;
  /**************************************************************************************/

  return 0;
}
