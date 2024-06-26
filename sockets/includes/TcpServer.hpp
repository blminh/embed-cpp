#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <atomic>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include "ClientHandler.hpp"

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

    void start();
    void receiver();
    void sender();
    void removeClient(int clientFd);

private:
    void doSend();
    void doReceive();

private:
    std::atomic<bool> running_;
    std::vector<std::shared_ptr<ClientHandler>> clientList_;
    std::thread senderThread_;
    std::thread receiverThread_;
    std::mutex mutex_;
    int serverFd_;
};

#endif