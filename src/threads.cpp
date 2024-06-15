#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <mutex>
#include <thread>
#include <future>
#include <chrono>
#include <condition_variable>
#include "../includes/threads.hpp"

namespace threads
{
    std::mutex mutex;

    // Counter
    Counter::Counter() {}
    Counter::~Counter() {}
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

    // Atomic Counter
    AtomicCounter::AtomicCounter() {}
    AtomicCounter::AtomicCounter(int val) : value{val} {}

    void AtomicCounter::increment()
    {
        ++value;
    }

    void AtomicCounter::decrement()
    {
        --value;
    }

    int AtomicCounter::get()
    {
        return value.load();
    }

    void AtomicCounter::atomicCounter()
    {
        AtomicCounter aCounter{10};
        std::cout << aCounter.get() << std::endl;
        aCounter.increment();
        std::cout << "After increment: " << aCounter.get() << std::endl;
        aCounter.decrement();
        aCounter.decrement();
        aCounter.decrement();
        std::cout << "After decrement: " << aCounter.get() << std::endl;
    }

    // future
    FutureThread::FutureThread() {}
    FutureThread::~FutureThread() {}

    void FutureThread::futureThread()
    {
        auto future = std::async(std::launch::async, []()
                                 { std::this_thread::sleep_for(std::chrono::seconds(5));
                           return 42; });
        std::cout << "Start: \n";
        std::cout << future.get() << std::endl;
        std::cout << "End: \n";
    }

    void FutureThread::futureWaitFor()
    {
        auto f1 = std::async(std::launch::async, []()
                             {
        std::this_thread::sleep_for(std::chrono::seconds(9));
        return 42; });

        auto f2 = std::async(std::launch::async, []()
                             {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 13; });

        auto f3 = std::async(std::launch::async, []()
                             {
        std::this_thread::sleep_for(std::chrono::seconds(6));
        return 666; });

        auto timeout = std::chrono::milliseconds(10);

        while (f1.valid() || f2.valid() || f3.valid())
        {
            if (f1.valid() && f1.wait_for(timeout) == std::future_status::ready)
            {
                std::cout << "Task1 is done! " << f1.get() << std::endl;
            }

            if (f2.valid() && f2.wait_for(timeout) == std::future_status::ready)
            {
                std::cout << "Task2 is done! " << f2.get() << std::endl;
            }

            if (f3.valid() && f3.wait_for(timeout) == std::future_status::ready)
            {
                std::cout << "Task3 is done! " << f3.get() << std::endl;
            }

            std::cout << "I'm doing my own work!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "I'm done with my own work!" << std::endl;
        }

        std::cout << "Everything is done, let's go back to the tutorial" << std::endl;
    }

    void FutureThread::futureRet()
    {
        auto future = std::async(std::launch::async, []()
                                 {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            return 42; });

        future.wait();
        std::cout << "After wait: " << future.get() << std::endl;
    }
};
