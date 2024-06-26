#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include <atomic>
#include <thread>
#include <mutex>
#include <sys/socket.h>

#define DATASIZE 128
#define PORT 8080

class TcpClient
{
public:
    TcpClient();
    ~TcpClient();

    void start();
    void receiver();
    void sender();
    bool getStatus();

private:
    void doReceive();
    void doSend(std::string msg);

private:
    int clientFd_;
    std::atomic<bool> running_;
    std::thread senderThread_;
    std::thread receiverThread_;
    std::mutex mutex_;
};

#endif