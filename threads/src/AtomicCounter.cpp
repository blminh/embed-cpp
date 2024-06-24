#include <iostream>
#include <thread>
#include "../includes/AtomicCounter.hpp"

namespace threads
{
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

    int AtomicCounter::getValue()
    {
        return mValue_.load();
    }
};
