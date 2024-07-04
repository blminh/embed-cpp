#include "TcpClient.hpp"
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <functional>
#include <arpa/inet.h>
#include <future>

TcpClient::TcpClient(std::string ip, int port) : running_{true}, ip_{ip}, port_{port}
{
    std::cout << "Constructor: " << ip << " - " << port << std::endl;
}

TcpClient::TcpClient() : running_{true}
{
}

TcpClient::~TcpClient()
{
    running_.store(false);
    if (senderThread_.joinable())
        senderThread_.join();
    if (receiverThread_.joinable())
        receiverThread_.join();
}

bool TcpClient::getStatus()
{
    return running_;
}

void TcpClient::start()
{
    clientFd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFd_ < 0)
    {
        std::cout << "Socket creation failed!" << std::endl;
        throw "Socket creation failed!";
        return;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port_);

    char ip[sizeof(ip_) + 1] = {0};
    snprintf(ip, sizeof(ip), "%s", ip_.c_str());
    if (inet_pton(AF_INET, ip, &serverAddress.sin_addr) <= 0)
    {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        throw "Invalid address/ Address not supported";
        return;
    }

    // connecting to server
    if (connect(clientFd_, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cout << "Connection failed!" << std::endl;
        throw "Connection failed!";
        return;
    }
}

void TcpClient::receiver()
{
    receiverThread_ = std::thread(std::bind(&TcpClient::doReceive, this));
}

void TcpClient::sender()
{
    senderThread_ = std::thread(std::bind(&TcpClient::doSend, this, ""));
}

void TcpClient::doReceive()
{
    bool isConnect = true;
    while (running_)
    {
        char buffer[DATASIZE + 1] = {0};
        int received = 0;
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
            std::cout << "Message from server: " << buffer << std::endl;
        }

        std::cout << "Running: " << running_ << std::endl;
        if (!isConnect)
        {
            std::cout << "Disconnected\n";
            running_.store(false);
            return;
        }
    }
}

void TcpClient::doSend(std::string msg)
{
    msg = "Hello, server! I am Client " + std::to_string(clientFd_);
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