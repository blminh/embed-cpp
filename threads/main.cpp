#include <vector>
#include <thread>
#include "includes/Counter.hpp"
#include "includes/AtomicCounter.hpp"
#include "includes/FutureThread.hpp"
#include "includes/SafeCounter.hpp"

int main()
{
    // >>> Counter :
    threads::Counter counter;
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

    // >>> SafeCounter:
    // threads::SafeCounter sCount;
    // std::vector<std::thread> threadList;
    // for (int i = 0; i < 3; i++)
    // {
    //     threadList.push_back(std::thread(
    //         [&sCount]()
    //         {
    //             for (int j = 0; j < 5; j++)
    //             {
    //                 sCount.increment();
    //             }
    //         }));
    // }

    // for (auto &thread : threadList)
    // {
    //     thread.join();
    // }

    // std::cout << sCount.getValue() << std::endl;

    // >>> AtomicCounter:
    // threads::AtomicCounter aCounter{10};
    // std::cout << aCounter.get() << std::endl;
    // aCounter.increment();
    // std::cout << "After increment: " << aCounter.get() << std::endl;
    // aCounter.decrement();
    // aCounter.decrement();
    // aCounter.decrement();
    // std::cout << "After decrement: " << aCounter.get() << std::endl;

    // >>> FutureThread:
    // threads::FutureThread fThread;
    // fThread.futureThread();
    // fThread.futureWaitFor();
    // fThread.futureRet();

    return 0;
}
