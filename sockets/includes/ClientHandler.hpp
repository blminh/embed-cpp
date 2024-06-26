#ifndef __CLIENT_HANDLER_H__
#define __CLIENT_HANDLER_H__

#include <atomic>
#include <thread>
#include <functional>

#define PORT 8080
#define DATASIZE 128

class ClientHandler
{
private:
    int clientFd_;
    std::atomic<bool> running_;
    std::thread receiverThread_;
    std::function<void(int)> closeCb_;

public:
    ClientHandler(int clientFd, std::function<void(int)> closeCb = nullptr);
    ~ClientHandler();

    const int getFd();
    void doSend(std::string msg);
    void doReceiver();
};

#endif