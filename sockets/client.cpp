#include <thread>
#include <chrono>
#include "TcpClient.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Format input: ./client your_ip your_port" << std::endl;
        return 0;
    }
    std::string ip(argv[1]);
    int port = atoi(argv[2]);

    TcpClient tcpClient(ip, port);
    tcpClient.start();
    tcpClient.sender();
    tcpClient.receiver();

    while (tcpClient.getStatus())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
