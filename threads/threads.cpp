#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <thread>
#include <future>
#include <chrono>
#include <condition_variable>
#include "includes/counter.hpp"
#include "includes/atomicCounter.hpp"
#include "includes/futureThread.hpp"
#include "includes/safeCounter.hpp"

namespace threads
{
    // Counter
    Counter::Counter() {}
    Counter::Counter(int value) : mValue_{value} {}
    Counter::~Counter() {}

    void Counter::increment()
    {
        mMutex_.lock();
        ++mValue_;
        mMutex_.unlock();
    }

    void Counter::decrement()
    {
        mMutex_.lock();
        try
        {
            std::cout << "Error" << std::endl;
            --mValue_;
        }
        catch (std::exception e)
        {

            mMutex_.unlock();
            std::cout << "Error: " << e.what() << std::endl;
            throw e;
        }
        mMutex_.unlock();
    }

    int Counter::getValue()
    {
        return mValue_;
    }

    void Counter::counter()
    {
        Counter counter;
        std::vector<std::thread> threadList;
        for (int i = 0; i < 5; i++)
        {
            threadList.push_back(std::thread(
                [&counter]()
                {
                    for (int j = 0; j < 10; j++)
                    {
                        counter.increment();
                    }
                }));
        }

        for (auto &thread : threadList)
        {
            thread.join();
        }

        std::cout << counter.getValue() << std::endl;
    }

    // SafeCounter
    SafeCounter::SafeCounter() {}
    SafeCounter::SafeCounter(int value) : mValue_{value} {}
    SafeCounter::~SafeCounter() {}

    void SafeCounter::increment()
    {
        std::lock_guard<std::mutex> guard(mMutex_);
        ++mValue_;
    }

    void SafeCounter::decrement()
    {
        std::lock_guard<std::mutex> guard(mMutex_);
        try
        {
            std::cout << "Error" << std::endl;
            --mValue_;
        }
        catch (std::exception e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            throw e;
        }
    }

    int SafeCounter::getValue()
    {
        return mValue_;
    }

    void SafeCounter::safeCounter()
    {
        SafeCounter counter;
        std::vector<std::thread> threadList;
        for (int i = 0; i < 3; i++)
        {
            threadList.push_back(std::thread(
                [&counter]()
                {
                    for (int j = 0; j < 5; j++)
                    {
                        counter.increment();
                    }
                }));
        }

        for (auto &thread : threadList)
        {
            thread.join();
        }

        std::cout << counter.getValue() << std::endl;
    }

    // Atomic Counter
    AtomicCounter::AtomicCounter() {}
    AtomicCounter::AtomicCounter(int val) : mValue_{val} {}

    void AtomicCounter::increment()
    {
        ++mValue_;
    }

    void AtomicCounter::decrement()
    {
        --mValue_;
    }

    int AtomicCounter::get()
    {
        return mValue_.load();
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
        auto future = std::async(std::launch::async,
                                 []()
                                 {
                                     std::this_thread::sleep_for(std::chrono::seconds(5));
                                     return 42;
                                 });
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
        auto future = std::async(std::launch::async,
                                 []()
                                 {
                                     std::this_thread::sleep_for(std::chrono::seconds(5));
                                     return 42;
                                 });

        future.wait();
        std::cout << "After wait: " << future.get() << std::endl;
    }
};
