#ifndef __SAFE_COUNTER_H__
#define __SAFE_COUNTER_H__

#include <mutex>

namespace threads
{
    class SafeCounter
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
        void safeCounter();
    };
};

#endif