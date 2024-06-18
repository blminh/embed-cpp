#include <iostream>
#include <vector>
#include <thread>
#include <stdexcept>
#include "../includes/counter.hpp"

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

    void Counter::counter()
    {
        Counter counter;
        std::vector<std::thread> threadList;
        for (int i = 0; i < 5; i++)
        {
            threadList.push_back(std::thread(
                [&counter]()
                {
                    for (int j = 0; j < 10; j++)
                    {
                        counter.increment();
                    }
                }));
        }

        for (auto &thread : threadList)
        {
            thread.join();
        }

        std::cout << counter.getValue() << std::endl;
    }
};
