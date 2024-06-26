#include <thread>
#include <chrono>
#include "TcpServer.hpp"

int main()
{
    TcpServer tcpServer;
    tcpServer.start();
    tcpServer.receiver();
    tcpServer.sender();
    tcpServer.remover();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
