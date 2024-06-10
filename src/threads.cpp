#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>
#include <stdexcept>

struct Counter
{
    int value;
    Counter() : value(0) {}
    Counter(int val) : value{val} {}

    void increment()
    {
        ++value;
    }

    void decrement()
    {
        if (value == 0)
        {
            throw "Value cannot be less than 0!";
        }

        --value;
    }
};

struct ConcurrentCounter
{
    std::mutex mutex;
    Counter counter;

    void increment()
    {
        mutex.lock();
        counter.increment();
        mutex.unlock();
    }

    void decrement()
    {
        mutex.lock();
        try
        {
            std::cout << "Error" << std::endl;
            counter.decrement();
        }
        catch (std::exception e)
        {

            mutex.unlock();
            std::cout << "Error: ";
            // throw e;
        }
        mutex.unlock();
    }
};

struct ConcurrentSafeCounter
{
    std::mutex mutex;
    Counter counter;

    void increment()
    {
        std::unique_lock<std::mutex> guard(mutex);
        counter.increment();
    }

    void decrement()
    {
        std::lock_guard<std::mutex> guard(mutex);
        counter.decrement();
    }
};

void hello()
{
    std::cout << "Hello from thread: " << std::this_thread::get_id() << std::endl;
}

int threads()
{
    // std::vector<std::thread> threads;
    // for (int i = 0; i < 5; ++i)
    // {
    //     threads.push_back(std::thread(hello));
    // }
    // for (auto &thread : threads)
    // {
    //     thread.join();
    // }

    Counter counter;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++)
    {
        threads.push_back(std::thread([&counter]()
                                      {
            for(int j=0; j<10; j++)
            {
                counter.increment();
            } }));
    }
    for (auto &thread : threads)
    {
        thread.join();
    }
    std::cout << counter.value << std::endl;

    Counter counter1{40};
    std::vector<std::thread> threads1;
    for (int i = 0; i < 5; i++)
    {
        threads1.push_back(std::thread([&counter1]()
                                       {
            for(int j=0; j<10; j++)
            {
                counter1.decrement();
            } }));
    }
    for (auto &thread : threads1)
    {
        thread.join();
    }
    std::cout << counter1.value << std::endl;

    return 0;
}