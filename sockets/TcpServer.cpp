
#include <functional>

class ClientHandler {
public:
    ClientHandler(int fd, std::function<void(int)> closeCb)
    : fd_ (fd)
    , running_{true}
    , closeCb_(closeCb)
    {
        revThr_ = std::thread(std::bind(&ClientHandler::receiver, this));
    }

    ~ClientHandler()
    {
        running_.store(false);
        if (revThr_.joinable()) revThr_.join();
    }

    void send(std::string msg)
    {
        // TODO: send to fd_
    }

    void receiver()
    {
        while (running_)
        {
            // TODO: rec from fd_

            // If client closed --> closeCb_(fd_);
        }
    }

    int fd_;
    std::atomic<bool> running_;
    std::thread revThr_;
    std::function<void(int)> closeCb_;
};
class TcpServer
{
public:

    TcpServer() : running_{true} {}

    ~TcpServer() {
        running_.store(false);
        if (senderThr_.joinable()) senderThr_.join();
    }

    void receiver()
    {
        revThr_ = std::thread(std::bind(&TcpServer::doReceive, this));
    }

    void sender()
    {    
        senderThr_ = std::thread(std::bind(&TcpServer::doSend, this));
    }

    void removeClient(int fd)
    {
        // lock
        // Search fd_ in clientList_ --> remove

        // unlock
    }

private:
    void doReceive()
    {
        while (running_) {
            // int fd = accept();

            // lock
            ClientHandler clientHandler(fd, std::bind(&TcpServer::removeClient, this, std::placeholders::_1));
            clientList_.push_back(clientHandler);
            // unlock
        }
    };
    
    void doSend()
    {
        std::string msg = "Server send msg ";
        while (running_) {
            // lock
            for (auto& it : clientList_) {
                it.send(msg);
            }
            // unlock

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

private:
    std::atomic<bool> running_;
    std::vector<ClientHandler> clientList_;
    std::thread senderThr_;
    std::thread revThr_;
    std::mutex mutex_;
};

int main()
{
    TcpServer tcpServer;
    tcpServer.receiver();
    tcpServer.sender();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}
