#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <atomic>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include "ClientHandler.hpp"
#include "BoundBuffer.hpp"

#define DATASIZE 128
#define PORT 8080

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

    void start();
    void receiver();
    void sender();
    void remover();
    auto findRemoveClient(int clientFd);

private:
    void doSend();
    void doReceive();
    void doRemoveClient();

private:
    std::atomic<bool> running_;
    std::vector<std::shared_ptr<ClientHandler>> clientList_;
    std::shared_ptr<BoundedBuffer<int>> delClientList_;
    std::thread senderThread_;
    std::thread receiverThread_;
    std::thread removerThread_;
    std::mutex mutex_;
    int serverFd_;
};

#endif