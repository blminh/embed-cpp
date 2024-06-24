#include <vector>
#include <thread>
#include "Counter.hpp"
#include "AtomicCounter.hpp"
#include "FutureThread.hpp"
#include "SafeCounter.hpp"
#include <condition_variable>

class BoundedBuffer
{
private:
    std::vector<int> mBuffer_;
    int mCapacity_;

    std::mutex mMutex_;

    std::condition_variable mNotFull_;
    std::condition_variable mNotEmpty_;

public:
    BoundedBuffer(int capacity) : mCapacity_{capacity}
    {
    }

    ~BoundedBuffer()
    {
    }

    void deposit(int data)
    {
        std::unique_lock<std::mutex> lock(mMutex_);
        mNotFull_.wait(lock,
                       [this]()
                       {
                           mBuffer_.size() == mCapacity_ ? std::cout << "Full! \n" : std::cout << "";
                           std::cout << std::endl;
                           return mBuffer_.size() != mCapacity_;
                       });
        mBuffer_.push_back(data);
        mNotEmpty_.notify_one();
    }

    int fetch()
    {
        std::unique_lock<std::mutex> lock(mMutex_);
        mNotEmpty_.wait(lock,
                        [this]()
                        {
                            mBuffer_.size() == 0 ? std::cout << "Empty!" : std::cout << "";
                            std::cout << std::endl;
                            return mBuffer_.size() != 0;
                        });
        int result = mBuffer_.front();
        // mBuffer_.pop_back();
        mBuffer_.erase(mBuffer_.begin());
        mNotFull_.notify_one();
        return result;
    }
};

void producer(int totalData, int id, BoundedBuffer &buffer)
{
    for (int i = 1; i < totalData + 1; ++i)
    {
        buffer.deposit(i);
        std::cout << "Produced - " << id << " deposit: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(int totalData, BoundedBuffer &buffer)
{
    for (int i = 0; i < totalData; ++i)
    {
        int value = buffer.fetch();
        std::cout << "Consumer fetched: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main()
{
    BoundedBuffer buffer(5);
    std::thread consumerThread(consumer, 15, std::ref(buffer));
    std::thread producerThread(producer, 15, 1, std::ref(buffer));
    // std::thread producerThread2(producer, 15, 2, std::ref(buffer));
    // std::thread producerThread3(producer, 15, 3, std::ref(buffer));

    consumerThread.join();
    producerThread.join();
    // producerThread2.join();
    // producerThread3.join();

    // >>> Counter :
    // threads::Counter counter;
    // std::vector<std::thread> threadList;
    // for (int i = 0; i < 5; i++)
    // {
    //     threadList.push_back(std::thread(
    //         [&counter]()
    //         {
    //             for (int j = 0; j < 10; j++)
    //             {
    //                 counter.increment();
    //             }
    //         }));
    // }

    // for (auto &thread : threadList)
    // {
    //     thread.join();
    // }

    // std::cout << counter.getValue() << std::endl;

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
