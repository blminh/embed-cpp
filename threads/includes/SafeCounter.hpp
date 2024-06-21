#ifndef __SAFE_COUNTER_H__
#define __SAFE_COUNTER_H__

#include <mutex>
#include "CounterBase.hpp"

namespace threads
{
    class SafeCounter : public CounterBase
    {
    private:
        int mValue_{};
        std::mutex mMutex_;

    public:
        SafeCounter();
        SafeCounter(int value);
        ~SafeCounter();

        void increment();
        void decrement();
        int getValue();
    };
};

#endif