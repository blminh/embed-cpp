#include <iostream>
#include <mutex>
#include <stdexcept>
#include <vector>
#include <thread>
#include "../includes/counter.h"

std::mutex mutex;

Counter::Counter()
{
}

Counter::~Counter()
{
}

Counter::Counter(int value) : m_value{value} {}

void Counter::increment()
{
    mutex.lock();
    ++m_value;
    mutex.unlock();
}

void Counter::decrement()
{
    mutex.lock();
    try
    {
        std::cout << "Error" << std::endl;
        --m_value;
    }
    catch (std::exception e)
    {

        mutex.unlock();
        std::cout << "Error: " << e.what() << std::endl;
        throw e;
    }
    mutex.unlock();
}

int Counter::getValue()
{
    return m_value;
}

void Counter::counter()
{
    Counter counter;
    std::vector<std::thread> threadList;
    for (int i = 0; i < 5; i++)
    {
        threadList.push_back(std::thread([&counter]()
                                         {
      for (int j = 0; j < 10; j++) {
        counter.increment();
      } }));
    }

    for (auto &thread : threadList)
    {
        thread.join();
    }

    std::cout << counter.getValue() << std::endl;
}
