#pragma once
#ifndef __THREADS_H__
#define __THREADS_H__

#include <atomic>

namespace threads
{

    class Counter
    {
    private:
        int m_value{};

    public:
        Counter();
        Counter(int value);
        ~Counter();

        void increment();
        void decrement();
        int getValue();
        void counter();
    };

    class AtomicCounter
    {
    private:
        std::atomic<int> value;

    public:
        AtomicCounter();
        AtomicCounter(int val);

        void increment();
        void decrement();

        int get();
        void atomicCounter();
    };

    class FutureThread
    {
    public:
        FutureThread();
        ~FutureThread();

        void futureThread();
        void futureWaitFor();
        void futureRet();
    };
};

#endif