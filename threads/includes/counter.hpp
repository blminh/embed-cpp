#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <mutex>

namespace threads
{
    class Counter
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