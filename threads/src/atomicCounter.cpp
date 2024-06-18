#include <iostream>
#include <thread>
#include "../includes/atomicCounter.hpp"

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
};
