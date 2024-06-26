#ifndef __CLIENT_HANDLER_H__
#define __CLIENT_HANDLER_H__

#include <atomic>
#include <thread>
#include <functional>
#include <memory>
#include "BoundBuffer.hpp"

#define DATASIZE 128

class ClientHandler
{
public:
    ClientHandler(int clientFd, std::shared_ptr<BoundedBuffer<int>> buffer);
    ~ClientHandler();

    const int getFd();
    void doSend(std::string msg);
    void doReceive();

private:
    int clientFd_;
    std::atomic<bool> running_;
    std::thread receiverThread_;
    std::shared_ptr<BoundedBuffer<int>> buffer_;
};

#endif