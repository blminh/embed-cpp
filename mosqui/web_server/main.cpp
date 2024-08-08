#include "CivetServer.h"
#include <cstring>
#include <iostream>
#include <unistd.h>

#include "ReceivedFromSystem.cpp"

#define DOCUMENT_ROOT "."
#define PORT "8080"
#define ROOT_URI "/home"
#define EXIT_URI "/exit"

/* Exit flag for main loop */
volatile bool exitNow = false;

class MyApiHandler : public CivetHandler
{
public:
    bool
    handleGet(CivetServer *server, struct mg_connection *conn)
    {
        const struct mg_request_info *request_info = mg_get_request_info(conn);
        // std::string response = "{\"message\": \"Hello, World!\"}";
        // mg_send_http_ok(conn, "application/json; charset=utf-8", response.length() + 1);
        // mg_write(conn, response.c_str(), response.length());
        // mg_write(conn, "\n", 1);

        std::string msg = "Hello";
        msg = returnData();
        std::cout << __LINE__ << "| " << msg << std::endl;
        mg_send_http_ok(conn, "application/json; charset=utf-8", msg.length() + 1);
        mg_write(conn, msg.c_str(), msg.length());
        mg_write(conn, "\n", 1);
        return true;
    }
};

class ExitHandler : public CivetHandler
{
public:
    bool
    handleGet(CivetServer *server, struct mg_connection *conn)
    {
        mg_printf(conn,
                  "HTTP/1.1 200 OK\r\nContent-Type: "
                  "text/plain\r\nConnection: close\r\n\r\n");
        mg_printf(conn, "Bye!\n");
        exitNow = true;
        return true;
    }
};

int main(int argc, char *argv[])
{
    mg_init_library(0);

    const char *options[] = {
        "document_root", DOCUMENT_ROOT,
        "listening_ports", PORT,
        0};

    std::vector<std::string> cpp_options;
    for (int i = 0; i < (sizeof(options) / sizeof(options[0]) - 1); i++)
    {
        cpp_options.push_back(options[i]);
    }

    CivetServer server(cpp_options);

    MyApiHandler mHandler;
    server.addHandler(ROOT_URI, mHandler);

    ExitHandler h_exit;
    server.addHandler(EXIT_URI, h_exit);

    receivedFromSystem();
    std::cout << "Run example at http://localhost:" << PORT << ROOT_URI << std::endl;
    std::cout << "Exit at http://localhost:" << PORT << EXIT_URI << std::endl;

    while (!exitNow)
    {
        sleep(1);
    }

    printf("Bye!\n");
    mg_exit_library();

    return 0;
}
