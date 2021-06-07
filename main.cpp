#include <iostream>
#include "task1.h"
#include "task2.h"
#include <condition_variable>

int main()
{
  // Task1
  //  std::vector<int> v1000;
  //  Task1::VectorPadding(v1000);
  //    std::array<std::thread, 10> threads;
  //    int step = 0;
  //    int inc100 = 0;
  //    for (int i = 0; i < 10; i++)
  //    {
  //      threads[i] = std::thread(task2::GetVectorSum, step, inc100);
  //      step += 1;
  //      inc100 += 100;
  //    }
  //    task2::go();
  //    for (auto& th : threads)
  //      th.join();
  // std::cout << Task1::GetSumv10() << std::endl;

  //    task2
  //    std::vector<int> a1000;
  //    std::vector<int> b1000;
  //    task2::VectorPaddings(a1000, b1000);
  //    std::array<std::thread, 10> threads;
  //    int step = 0;
  //    int inc100 = 0;
  //    for (int i = 0; i < 10; i++)
  //    {
  //      threads[i] = std::thread(task2::GetScalarProduct, a1000, b1000, step, inc100);
  //      step += 1;
  //      inc100 += 100;
  //    }
  //    for (auto& th : threads)
  //      th.join();

  //    std::cout << task2::GetSumv10() << std::endl;

  //  std::cout << task2::GetSumv10() << std::endl;

  // task3

  std::vector<int> a1000;
  std::vector<int> b1000;
  task2::VectorPaddings(a1000, b1000);
  std::array<std::thread, 10> threads;
  int step = 0;
  int inc100 = 0;
  for (int i = 0; i < 10; i++)
  {
    threads[i] = std::thread(task2::GetScalarProduct, a1000, b1000, step, inc100);
    step += 1;
    inc100 += 100;
    std::cout << threads[i].get_id() << std::endl;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  task2::go();
  for (auto& th : threads)
    th.join();

  std::cout << task2::GetSumv10() << std::endl;

  return 0;
}
