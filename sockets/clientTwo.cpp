#include <thread>
#include <chrono>
#include "TcpClient.hpp"

int main()
{
    TcpClient tcpClient;
    tcpClient.start();
    tcpClient.sender();
    tcpClient.receiver();

    while (tcpClient.getStatus())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
