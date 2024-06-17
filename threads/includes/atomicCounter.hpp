#ifndef __ATOMIC_COUNTER_H__
#define __ATOMIC_COUNTER_H__

#include <atomic>

namespace threads
{
    class AtomicCounter
    {
    private:
        std::atomic<int> mValue_;

    public:
        AtomicCounter();
        AtomicCounter(int val);

        void increment();
        void decrement();

        int get();
        void atomicCounter();
    };
};

#endif