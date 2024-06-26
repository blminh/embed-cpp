#ifndef __BOUND_BUFFER_H__
#define __BOUND_BUFFER_H__

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>

template <typename T>
class BoundedBuffer
{
public:
#include "BoundBuffer.hpp"

    BoundedBuffer(int capacity) : capacity_{capacity} {}

    ~BoundedBuffer() {}

    void deposit(T data)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        notFull_.wait(lock, [this]()
                      { return buffer_.size() != capacity_; });

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
                           return buffer_.size() != 0;
                       });

        T result = buffer_.front();
        buffer_.erase(buffer_.begin());
        lock.unlock();
        notFull_.notify_one();
        return result;
    }

private:
    std::vector<T> buffer_;
    int capacity_;
    std::mutex mutex_;
    std::condition_variable notFull_;
    std::condition_variable notEmpty_;
};

#endif