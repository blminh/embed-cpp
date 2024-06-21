#ifndef __ATOMIC_COUNTER_H__
#define __ATOMIC_COUNTER_H__

#include <atomic>
#include "CounterBase.hpp"

namespace threads
{
    class AtomicCounter : public CounterBase
    {
    private:
        std::atomic<int> mValue_;

    public:
        AtomicCounter();
        AtomicCounter(int val);

        void increment();
        void decrement();

        int getValue();
    };
};

#endif