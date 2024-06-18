#include <iostream>
#include <stdexcept>
#include <vector>
#include <thread>
#include "../includes/safeCounter.hpp"

namespace threads
{
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
};
