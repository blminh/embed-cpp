#include <stdexcept>
#include "../includes/Counter.hpp"

namespace threads
{
    Counter::Counter() {}
    Counter::Counter(int value) : mValue_{value} {}
    Counter::~Counter() {}

    void Counter::increment()
    {
        mMutex_.lock();
        ++mValue_;
        mMutex_.unlock();
    }

    void Counter::decrement()
    {
        mMutex_.lock();
        try
        {
            std::cout << "Error" << std::endl;
            --mValue_;
        }
        catch (std::exception e)
        {

            mMutex_.unlock();
            std::cout << "Error: " << e.what() << std::endl;
            throw e;
        }
        mMutex_.unlock();
    }

    int Counter::getValue()
    {
        return mValue_;
    }
};
