#include "ClientHandler.hpp"
#include <iostream>
#include <sys/socket.h>

ClientHandler::ClientHandler(int clientFd, std::function<void(int)> closeCb)
    : clientFd_(clientFd), running_{true}, closeCb_(closeCb)
{
    receiverThread_ = std::thread(std::bind(&ClientHandler::doReceiver, this));
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
    char sMsg[DATASIZE] = {0};
    snprintf(sMsg, sizeof(sMsg), "%s", msg.c_str());
    int sent = 0;
    while (sent < DATASIZE)
    {

        int len = send(clientFd_, sMsg + sent, DATASIZE - sent, 0);
        if (len < 0)
        {
            std::cout << "Send fail!" << std::endl;
            return;
        }
        sent += len;
    }
}

void debugMsg()
{
    std::cout << __FUNCTION__ << "|" << __LINE__ << std::endl;
}

void ClientHandler::doReceiver()
{
    while (running_)
    {
        char buffer[DATASIZE + 1] = {0};
        int received = 0;
        bool isConnect = true;
        while (received < DATASIZE)
        {
            auto len = recv(clientFd_, &buffer[received], DATASIZE - received, MSG_NOSIGNAL);
            std::cout << "fd: " << clientFd_ << std::endl;
            std::cout << "fd - leng: " << len << std::endl;
            std::cout << "fd - buffer: " << buffer << std::endl;
            if (len < 0)
            {
                std::cout << "Received data fail" << std::endl;
                isConnect = false;
                break;
                // return;
            }
            else if (len == 0)
            {
                std::cout << "Socket is closed" << std::endl;
                isConnect = false;
                break;
                // return;
            }
            received += len;
            // std::cout << "Message from client: " << buffer << std::endl;
        }

        std::cout << "Message from client: " << buffer << std::endl;
        // If client closed --> closeCb_(fd_);
        if (!isConnect)
        {
            ClientHandler::closeCb_(clientFd_);
            return;
        }
    }
}
