#include <iostream>
#include <thread>
#include <vector>
#include <array>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <numeric>
#include <future>

using namespace std;

int partialSum(const vector<int>& vector, size_t from, size_t to)
{
    auto sum = 0;
    for (auto i = from; i < to; i++)
    {
        sum += vector.at(i);
    }
    return sum;
}

void FirstTask()
{
    vector<future<int>> futures;
    vector<int> v1(1000);
    std::iota(v1.begin(), v1.end(), 1);

    for (auto i = 0; i < 1000; i += 100)
    {
         futures.push_back(async(launch::async, partialSum, ref(v1), i, i + 100));
    }
    auto globalsum = 0;
    for (auto& e : futures)
    {
        globalsum += e.get();
    }

    cout << "Task 1 sum: " << globalsum << endl;
}

static mutex mtx;
static condition_variable cv;

static array<int, 1000> save;

static atomic<int> counter = 0;

int ScalarMultiplication(const vector<int>& v1, const vector<int>& v2, size_t from, size_t to)
{
    for (auto i = from; i < to; i++)
    {
        save[i] = (v1.at(i) * v2.at(i));
    }

    counter++;

    unique_lock<mutex> lck(mtx);

    cv.wait(lck, [] { return counter == 10; });


    auto localsum = 0;
    for (auto i = from; i < to; i++)
    {
        localsum += save[i];
    }
    return localsum;
}

void SecondAndThirdTask()
{
    vector<int> v1(1000);
    vector<int> v2(1000);
    std::iota(v1.begin(), v1.end(), 1);
    std::iota(v2.begin(), v2.end(), 1);
    vector<future<int>> futures;

    for (auto i = 0; i < 1000; i += 100)
    {
        futures.push_back(async(launch::async, ScalarMultiplication, ref(v1), ref(v2), i, i + 100));
    }

    cv.notify_all();

    int finalsum = 0;
    for (auto& e : futures)
    {
        finalsum += e.get();
    }
    cout << "Task 2 and 3 scalar multiplication: " << finalsum << endl;
}

int main()
{
    FirstTask();
    SecondAndThirdTask();
    return 0;
}
