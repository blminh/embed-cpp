#include "TcpServer.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

TcpServer::TcpServer() : running_{true}, delClientList_(new BoundedBuffer<int>(10))
{
}

TcpServer::~TcpServer()
{
    running_.store(false);
    if (senderThread_.joinable())
        senderThread_.join();
    if (receiverThread_.joinable())
        receiverThread_.join();
    if (removerThread_.joinable())
        removerThread_.join();
}

void TcpServer::start()
{
    serverFd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd_ == 0)
    {
        std::cout << "Socket failed!!!" << std::endl;
        throw "Socket failed!!!";
        return;
    }

    // forcefully attaching socket to the port 8080
    int opt = 1;
    if (setsockopt(serverFd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cout << "Setsockopt failed!" << std::endl;
        throw "Setsockopt failed!";
        return;
    }

    sockaddr_in serverAddr;
    int serverAddrLen = sizeof(serverAddr);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind
    if (bind(serverFd_, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cout << "serverFd: " << serverFd_ << std::endl;
        std::cout << "Bind failed!" << std::endl;
        throw "Bind failed!";
        return;
    }

    // Listen
    if (listen(serverFd_, 3) < 0)
    {
        std::cout << "Listen failed!" << std::endl;
        throw "Listen failed!";
        return;
    }
}

void TcpServer::receiver()
{
    receiverThread_ = std::thread(std::bind(&TcpServer::doReceive, this));
}

void TcpServer::sender()
{
    senderThread_ = std::thread(std::bind(&TcpServer::doSend, this));
}

void TcpServer::remover()
{
    removerThread_ = std::thread(std::bind(&TcpServer::doRemoveClient, this));
}

void TcpServer::doRemoveClient()
{
    while (running_)
    {
        auto data = delClientList_->fetch();
        std::lock_guard<std::mutex> lock(mutex_);
        auto itr = clientList_.begin();
        while (itr != clientList_.end())
        {
            if (itr->get()->getFd() == data)
            {
                std::cout << "Remove " << itr->get()->getFd() << std::endl;
                clientList_.erase(itr);
                break;
            }
            itr++;
        }
    }
}

void TcpServer::doReceive()
{
    while (running_)
    {
        // accept
        sockaddr_in clientAddr;
        int clientAddrLen = sizeof(clientAddr);
        int clientFd = accept(serverFd_, (struct sockaddr *)&clientAddr, (socklen_t *)&clientAddrLen);
        std::cout << "New connection fd=" << clientFd
                  << ", client >> " << std::string(inet_ntoa(clientAddr.sin_addr)) << std::endl;
        if (clientFd < 0)
        {
            std::cout << "Accept failed!" << std::endl;
            throw "Accept failed!";
            return;
        }

        std::shared_ptr<ClientHandler> clientHandler = std::make_shared<ClientHandler>(clientFd, delClientList_);
        {
            std::lock_guard<std::mutex> lock(mutex_);
            clientList_.push_back(clientHandler);
        }
    }
};

void TcpServer::doSend()
{
    std::string msg = "Server send msg ";
    while (running_)
    {
        try
        {
            mutex_.lock();
            for (auto &it : clientList_)
            {
                it->doSend(msg);
            }
            mutex_.unlock();
        }
        catch (std::exception &e)
        {
            std::cout << "Error doSend(): " << e.what() << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
