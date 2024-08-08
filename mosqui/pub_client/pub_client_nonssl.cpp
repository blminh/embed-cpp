#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <signal.h>
#include <mosquitto.h>
#include <nlohmann/json.hpp>
#include "temperatureCpu.cpp"
#include "ramUsage.cpp"
#include "cpuUsage.cpp"
#include "listApps.cpp"

static int run = -1;
std::mutex mutex;

void log(int line, int rc = 0, std::string msg = "default")
{
    std::cout << "Line: " << line << " | rc: " << rc << " | Msg: " << msg << std::endl;
}

void handle_sigint(int signal)
{
    std::cout << "Catch signal: " << signal << std::endl;
    exit(1);
}

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
    if (rc != 0)
    {
        log(__LINE__, rc, "Connect failed with code");
    }
    else
    {
        log(__LINE__, rc, "Connected to the broker");
        std::lock_guard<std::mutex> lock(mutex);
        run = -1;
    }
}

void on_disconnect(struct mosquitto *mosq, void *obj, int rc)
{
    log(__LINE__, rc, "disconnect broker");
}

int main(int argc, char *argv[])
{
    int rc;
    struct mosquitto *mosq = NULL;

    signal(SIGINT, handle_sigint);
    signal(SIGSEGV, handle_sigint);

    mosquitto_lib_init();
    mosq = mosquitto_new("pub_client", true, NULL);
    if (mosq == NULL)
    {
        return -1;
    }

    std::string willMsg = "Client disconnected unexpectedly";
    rc = mosquitto_will_set(mosq, "home", willMsg.length(), willMsg.c_str(), 1, 0);
    if (rc != MOSQ_ERR_SUCCESS)
    {
        return -1;
    }
    log(__LINE__, rc, "will message");

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);

    rc = mosquitto_connect(mosq, "0.0.0.0", 1883, 60);

    if (rc != MOSQ_ERR_SUCCESS)
    {
        log(__LINE__, rc, "Reconnecting ...");
        return -1;
    }

    while (1)
    {
        std::string str = "Hello from pub_client!";
        mosquitto_publish(mosq, NULL, "home", str.length(), str.c_str(), 1, true);

        std::string list = listRunningProcesses();
        mosquitto_publish(mosq, NULL, "home", list.size(), list.c_str(), 1, true);

        // std::string strTemp = temperatureCpu();
        // mosquitto_publish(mosq, NULL, "home", strTemp.length(), strTemp.c_str(), 1, true);

        // std::string strRamUsage = ramUsage();
        // mosquitto_publish(mosq, NULL, "home", strRamUsage.length(), strRamUsage.c_str(), 1, true);

        // std::string strCpuUsage = cpuUsage();
        // mosquitto_publish(mosq, NULL, "home", strCpuUsage.length(), strCpuUsage.c_str(), 1, true);
        sleep(5);
    }

    while (run == -1)
    {
        rc = mosquitto_loop(mosq, -1, 1);
        if (rc != MOSQ_ERR_SUCCESS)
        {
            mosquitto_reconnect_delay_set(mosq, 1000, 10000, true);
            rc = mosquitto_reconnect(mosq);
            log(__LINE__, rc, "Reconnecting ...");
        }
    }

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return run;
}
