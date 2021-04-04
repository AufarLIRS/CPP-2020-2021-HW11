#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <numeric>

// multithreaded_ranges
template <typename Iterator, typename Func>
auto multithreaded_ranges(Iterator begin, Iterator end, Func&& func)
{
  //  int thread_count = std::thread::hardware_concurrency(); - Создает 4 потока

  auto size = std::distance(begin, end);
  int thread_count = 10;
  std::cout << "Hardware threads: " << thread_count << std::endl;

  std::vector<std::thread> threads;
  std::vector<typename std::iterator_traits<Iterator>::value_type> mins(thread_count);

  auto first = begin;
  auto last = first;
  size /= thread_count;

  for (int i = 0; i < thread_count; ++i)
  {
    first = last;
    if (i == thread_count - 1)
      last = end;
    else
      std::advance(last, size);

    threads.emplace_back([first, last, &func, &r = mins[i]]() { r = std::forward<Func>(func)(first, last); });
  }

  for (auto& t : threads)
    t.join();

  return std::forward<Func>(func)(std::begin(mins), std::end(mins));
}

// vector_sum
template <typename Iterator>
auto vector_sum(Iterator begin, Iterator end)
{
  return multithreaded_ranges(begin, end, [](auto b, auto e) { return std::accumulate(b, e, 0); });
}

// DotProductOfVectors
//template <typename Iterator>
//auto DotProductOfVectors(Iterator v1_begin, Iterator v1_end)
//{
//  return multithreaded_ranges(v1_begin, v1_end, [](auto b1, auto e1) { return std::inner_product(b1, e1); });
//}

// First Task
void task1()
{
  const size_t count = 1000;
  std::vector<int> data1(count);
  generate(data1.begin(), data1.end(), rand);

  auto task1_result = vector_sum(std::begin(data1), std::end(data1));
  std::cout << "Sum of vectors = " << task1_result << std::endl;
}

// Second Task
//void task2()
//{
//  const size_t count = 1000;
//  std::vector<int> data1(count);
//  generate(data1.begin(), data1.end(), rand);
//  std::vector<int> data2(count);
//  generate(data2.begin(), data2.end(), rand);

//  auto task2_result = DotProductOfVectors(std::begin(data1), std::end(data1));
//  std::cout << "Dot product of vectors  = " << task2_result << std::endl;
//}

int main()
{
  task1();
//  task2();

  return 0;
}
