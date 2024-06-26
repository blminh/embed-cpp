#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <functional>
#include <thread>
#include <vector>

template <typename T>
class BoundedBuffer
{
private:
    std::vector<T> buffer_;
    int capacity_;

    std::mutex mutex_;

    std::condition_variable notFull_;
    std::condition_variable notEmpty_;

    BoundedBuffer(int capacity) : capacity_(capacity)
    {
    }

    BoundedBuffer()
    {
    }

    ~BoundedBuffer()
    {
    }

    void deposit(T data)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        notFull_.wait(lock, [this]()
                      { return sizeof(buffer_) != capacity; });

        buffer_.push_back(data);
        lock.unlock();
        notEmpty_.notify_one();
    }

    T fetch()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        notEmpty_.wait(lock,
                       [this]()
                       {
                           return sizeof(buffer_) != 0;
                       });

        T result = buffer_.pop();
        lock.unlock();
        notFull_.notify_one();
        return result;
    }
};