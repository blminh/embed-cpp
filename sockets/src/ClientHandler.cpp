#include "ClientHandler.hpp"
#include <iostream>
#include <sys/socket.h>

ClientHandler::ClientHandler(int clientFd, std::shared_ptr<BoundedBuffer<int>> buffer = nullptr)
    : clientFd_(clientFd), running_{true}, buffer_(buffer)
{
    receiverThread_ = std::thread(std::bind(&ClientHandler::doReceive, this));
}

ClientHandler::~ClientHandler()
{
    running_.store(false);
    if (receiverThread_.joinable())
        receiverThread_.join();
}

const int ClientHandler::getFd()
{
    return clientFd_;
}

void ClientHandler::doSend(std::string msg)
{
    char sMsg[DATASIZE + 1] = {0};
    snprintf(sMsg, sizeof(sMsg), "%s", msg.c_str());
    int sent = 0;
    while (sent < DATASIZE)
    {

        int len = send(clientFd_, sMsg + sent, DATASIZE - sent, MSG_NOSIGNAL);
        if (len < 0)
        {
            std::cout << "Send fail!" << std::endl;
            return;
        }
        sent += len;
    }
}

void ClientHandler::doReceive()
{
    while (running_)
    {
        char buffer[DATASIZE + 1] = {0};
        int received = 0;
        bool isConnect = true;
        while (received < DATASIZE)
        {
            auto len = recv(clientFd_, &buffer[received], DATASIZE - received, MSG_NOSIGNAL);
            if (len < 0)
            {
                std::cout << "Received data fail" << std::endl;
                isConnect = false;
                break;
            }
            else if (len == 0)
            {
                std::cout << "Socket is closed" << std::endl;
                isConnect = false;
                break;
            }
            received += len;
            std::cout << "Message from client: " << buffer << std::endl;
        }

        if (!isConnect)
        {
            buffer_->deposit(clientFd_);
            return;
        }
    }
}
