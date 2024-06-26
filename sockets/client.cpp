#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <chrono>
#include <future>

#define DATASIZE 128

int receivedData(int socket)
{
    char buffer[DATASIZE + 1] = {0};
    int received = 0;
    try
    {
        while (received < DATASIZE)
        {
            auto len = recv(socket, &buffer[received], DATASIZE - received, 0);
            if (len < 0)
            {
                std::cout << "Received data fail" << std::endl;
                return -1;
            }
            else if (len == 0)
            {
                std::cout << "Socket is closed" << std::endl;
                return -1;
            }
            received += len;
            std::cout << "Message from server: " << buffer << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Received | " << e.what() << std::endl;
    }

    return 0;
}

int sendData(int socket, char *data)
{
    int sent = 0;
    while (sent < DATASIZE)
    {
        int len = send(socket, data + sent, DATASIZE - sent, 0);
        if (len < 0)
        {
            std::cout << "Send fail!" << std::endl;
            return -1;
        }
        sent += len;
    }
    return 0;
}

int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        std::cout << "Socket creation failed!" << std::endl;
        return -1;
    }
    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // connecting to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cout << "Connection failed!" << std::endl;
        return -1;
    }

    // sending data
    std::string message = "Hello, server! I am Client " + std::to_string(clientSocket);
    char sMsg[DATASIZE] = {0};
    snprintf(sMsg, sizeof(sMsg), "%s", message.c_str());
    send(clientSocket, sMsg, strlen(sMsg), 0);
    std::thread sendThread(sendData, clientSocket, sMsg);
    sendThread.join();

    while (true)
    {
        // recv data from server
        // std::thread receivedThread(receivedData, clientSocket);
        // receivedThread.join();
        std::future<int> status = std::async(std::launch::async, receivedData, clientSocket);

        if (status.valid() && status.get() == -1)
            break;
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
