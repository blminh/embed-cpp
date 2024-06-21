#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <iostream>
#include <mutex>
#include "CounterBase.hpp"

namespace threads
{
    class Counter : public CounterBase
    {
    private:
        int mValue_{};
        std::mutex mMutex_;

    public:
        Counter();
        Counter(int value);
        ~Counter();

        void increment();
        void decrement();
        int getValue();
        void counter();
    };
};

#endif