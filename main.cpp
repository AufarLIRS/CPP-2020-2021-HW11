#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <numeric>
#include <future>
#include <execution>

// multithreaded_ranges
template <typename Iterator, typename Func>
auto multithreaded_ranges_1(Iterator begin, Iterator end, Func&& func)
{
  auto size = std::distance(begin, end);
  int task_count = 10;
  std::cout << "Hardware threads: " << task_count << std::endl;
  std::vector<std::future<typename std::iterator_traits<Iterator>::value_type>> tasks;

  auto first = begin;
  auto last = first;
  size /= task_count;

  for (int i = 0; i < task_count; ++i)
  {
    first = last;
    if (i == task_count - 1)
      last = end;
    else
      std::advance(last, size);

    tasks.emplace_back(
        std::async(std::launch::async, [first, last, &func]() { return std::forward<Func>(func)(first, last); }));
  }

  std::vector<typename std::iterator_traits<Iterator>::value_type> mins;

  for (auto& t : tasks)
    mins.push_back(t.get());

  return std::forward<Func>(func)(std::begin(mins), std::end(mins));
}

// vector_sum
template <typename Iterator>
auto vector_sum(Iterator begin, Iterator end)
{
  return multithreaded_ranges_1(begin, end, [](auto b, auto e) { return std::accumulate(b, e, 0); });
}

// DotProductOfVectors
template <typename Iterator>
auto DotProductOfVectors(Iterator v1_begin, Iterator v1_end, Iterator v2_begin)
{
  return std::transform(std::execution::par, v1_begin, v1_end, v2_begin,
                        std::inner_product(v1_begin, v1_end, v2_begin, 0));
}

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
void task2()
{
  const size_t count = 1000;
  std::vector<int> data1(count);
  generate(data1.begin(), data1.end(), rand);
  std::vector<int> data2(count);
  generate(data2.begin(), data2.end(), rand);

  auto task2_result = DotProductOfVectors(std::begin(data1), std::end(data1), std::begin(data2));
  //std::cout << "Dot product of vectors  = " << task2_result << std::endl;
}

int main()
{
  task1();
  task2();

  return 0;
}
