#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fstream>
#include <unistd.h>

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
    // connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cout << "Connection failed!" << std::endl;
        return -1;
    }

    // sending data
    const char *message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    while (true)
    {
        // recv data from server
        char buffer[1024] = {0};
        // int valRead = read(clientSocket, buffer, 1024);
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::cout << "Message from server: " << buffer << std::endl;
    }
    return 0;
}
