#include <iostream>
#include "task1.h"
#include "task2.h"
#include <condition_variable>

int main()
{
  // Task1
  //  std::vector<int> v1000;
  //  Task1::VectorPadding(v1000);
  //  std::thread t1(Task1::GetVectorSum, v1000, 0, 0);
  //  std::thread t2(Task1::GetVectorSum, v1000, 1, 100);
  //  std::thread t3(Task1::GetVectorSum, v1000, 2, 200);
  //  std::thread t4(Task1::GetVectorSum, v1000, 3, 300);
  //  std::thread t5(Task1::GetVectorSum, v1000, 4, 400);
  //  std::thread t6(Task1::GetVectorSum, v1000, 5, 500);
  //  std::thread t7(Task1::GetVectorSum, v1000, 6, 600);
  //  std::thread t8(Task1::GetVectorSum, v1000, 7, 700);
  //  std::thread t9(Task1::GetVectorSum, v1000, 8, 800);
  //  std::thread t10(Task1::GetVectorSum, v1000, 9, 900);

  //  t1.join();
  //  t2.join();
  //  t3.join();
  //  t4.join();
  //  t5.join();
  //  t6.join();
  //  t7.join();
  //  t8.join();
  //  t9.join();
  //  t10.join();
  // std::cout << Task1::GetSumv10() << std::endl;
  // task2
  //  std::vector<int> a1000;
  //  std::vector<int> b1000;
  //  task2::VectorPaddings(a1000, b1000);
  //  std::thread th1(task2::GetScalarProduct, a1000, b1000, 0, 0);
  //  std::thread th2(task2::GetScalarProduct, a1000, b1000, 1, 100);
  //  std::thread th3(task2::GetScalarProduct, a1000, b1000, 2, 200);
  //  std::thread th4(task2::GetScalarProduct, a1000, b1000, 3, 300);
  //  std::thread th5(task2::GetScalarProduct, a1000, b1000, 4, 400);
  //  std::thread th6(task2::GetScalarProduct, a1000, b1000, 5, 500);
  //  std::thread th7(task2::GetScalarProduct, a1000, b1000, 6, 600);
  //  std::thread th8(task2::GetScalarProduct, a1000, b1000, 7, 700);
  //  std::thread th9(task2::GetScalarProduct, a1000, b1000, 8, 800);
  //  std::thread th10(task2::GetScalarProduct, a1000, b1000, 9, 900);

  //  th1.join();
  //  th2.join();
  //  th3.join();
  //  th4.join();
  //  th5.join();
  //  th6.join();
  //  th7.join();
  //  th8.join();
  //  th9.join();
  //  th10.join();

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
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  task2::go();
  for (auto& th : threads)
    th.join();

  std::cout << task2::GetSumv10() << std::endl;

  return 0;
}
