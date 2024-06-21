#include <iostream>
#include <stdexcept>
#include <vector>
#include <thread>
#include "../includes/SafeCounter.hpp"

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
};
