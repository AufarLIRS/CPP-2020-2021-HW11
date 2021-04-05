#include "Task2.h"

std::vector<int> vectorPartProducts;  //общий вектор произведений элементов векторов

void ProductVectors(std::vector<int>& vec1, std::vector<int>& vec2, int start, int end, int i)
{
  int product;
  for (int i = start; i < end; i++)
  {
    product = vec1[i] * vec2[i];
    vectorPartProducts[i] = product;
  }
  std::cout << "Thread #" << i << " has put his products to the common vector in [" << start << ";" << end << ")"
            << std::endl;
  std::cout << "Thread #" << i << " has ended to work" << std::endl;
}

std::vector<int> Start2(int vectorLength)
{
  std::vector<int> vec1(vectorLength, 3);
  std::vector<int> vec2(vectorLength, 5);
  vectorPartProducts.resize(vectorLength);

  std::array<std::thread, 10> threads;

  int step = vectorLength / 10;
  int start = 0;
  int end = step;

  for (int i = 0; i < 10; i++)
  {
    threads[i] = std::thread(ProductVectors, std::ref(vec1), std::ref(vec2), start, end, i);
    start += step;
    end += step;
  }

  for (auto& th : threads)
    th.join();
  return vectorPartProducts;
}
