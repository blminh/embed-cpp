#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
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
            std::cout << "Leng data: " << len << std::endl;
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

void receivedThread(int socket)
{
    std::thread receivedThread(
        [socket]()
        {
            while (true)
            {
                int rd = receivedData(socket);
                std::cout << "Received: " << rd << std::endl;
                std::cout << "Received - socket: " << socket << std::endl;
                if (rd <= 0)
                {
                    return;
                }
            }
        });
    receivedThread.join();
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
    std::cout << "Sent done!" << std::endl;
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
    // serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    // connecting to server
    // connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cout << "Connection failed!" << std::endl;
        return -1;
    }

    // sending data
    std::string message = "Hello, server! I am Client " + std::to_string(clientSocket);
    char sMsg[DATASIZE + 1] = {0};
    snprintf(sMsg, sizeof(sMsg), "%s", message.c_str());
    sendData(clientSocket, sMsg);

    // recv data from serverAddr
    // receivedThread(clientSocket);

    while (true)
    {
        std::future<int> status = std::async(std::launch::async, receivedData, clientSocket);
        if (status.valid() && status.get() == -1)
            break;
        std::thread receivedThread(receivedData, clientSocket);
        receivedThread.join();
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
