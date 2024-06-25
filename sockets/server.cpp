#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <exception>

int main()
{
    int serverFd, clientSocket, valRead;
    struct sockaddr_in address; // netinet/in.h -> sockaddr_in
    int opt = 1;
    int addrlen = sizeof(address);
    const char *hello = "Hello from server!";

    // creating socket file description
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == 0)
    {
        std::cout << "Socket failed!!!" << std::endl;
        return -1;
    }

    // forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Setsockopt failed!");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed!");
        exit(EXIT_FAILURE);
    }
    // listen(serverFd, 3);
    if (listen(serverFd, 5) < 0)
    {
        std::cout << "Listen failed!" << std::endl;
        return -1;
    }

    std::vector<int> clientList;
    try
    {
        while (true)
        {

            clientSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
            if (clientSocket < 0)
            {
                std::cout << "Accept failed!" << std::endl;
                return -1;
            }

            std::cout << "Client socket: " << clientSocket << std::endl;

            char buffer[1024] = {0};
            try
            {
                recv(clientSocket, buffer, sizeof(buffer), 0);
            }
            catch (std::exception e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }

            std::cout << "Message from client: " << buffer << std::endl;

            int isClientExisted = std::count(clientList.begin(), clientList.end(), clientSocket);
            // Check if the target value was found
            if (isClientExisted <= 0)
            {
                clientList.push_back(clientSocket);
                try
                {
                    send(clientSocket, hello, strlen(hello), 0);
                }
                catch (std::exception e)
                {
                    std::cout << "Error: " << e.what() << std::endl;
                }
            }
            // Send to all client
            for (auto client = clientList.begin(); client != clientList.end(); client++)
            {
                std::string msg = "Add new client " + std::to_string(clientSocket);
                try
                {
                    send(*client, msg.c_str(), msg.length(), 0);
                }
                catch (std::exception e)
                {
                    std::cout << "Error: " << e.what() << std::endl;
                }
            }
        }
    }
    catch (...)
    {
        std::cout << "Error: " << std::endl;
    }
    return 0;
}
