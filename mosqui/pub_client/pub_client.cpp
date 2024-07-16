#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <signal.h>
#include <openssl/ssl.h>
#include <mosquitto.h>
#include <nlohmann/json.hpp>
#include "temperatureCpu.cpp"
#include "ramUsage.cpp"
#include "cpuUsage.cpp"

static int run = -1;
std::mutex mutex;

struct Client
{
    std::string cafile_;
    std::string certfile_;
    std::string keyfile_;
    std::string tlsVersion_;
    std::string host_;
    std::string port_;
    std::vector<std::string> topic_;
};

Client readConfig(std::string filepath)
{
    std::ifstream conf(filepath);
    nlohmann::json confJson = nlohmann::json::parse(conf);

    Client client;
    client.cafile_ = confJson["ca_file"];
    client.certfile_ = confJson["certfile"];
    client.keyfile_ = confJson["key_file"];
    client.tlsVersion_ = confJson["tls_version"];
    client.host_ = confJson["host"];
    client.port_ = confJson["port"];
    client.topic_ = confJson["topic"];
    return client;
}

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

    Client client = readConfig("config.json");

    std::string willMsg = "Client disconnected unexpectedly";
    rc = mosquitto_will_set(mosq, client.topic_[0].c_str(), willMsg.length(), willMsg.c_str(), 1, 0);
    if (rc != MOSQ_ERR_SUCCESS)
    {
        return -1;
    }
    log(__LINE__, rc, "will message");

    // rc = mosquitto_will_clear(mosq);
    // if (rc != MOSQ_ERR_SUCCESS)
    // {
    //     return -1;
    // }
    // log(__LINE__, rc, "will clear message");

    mosquitto_tls_opts_set(mosq, 1, client.tlsVersion_.c_str(), NULL);
    mosquitto_tls_set(mosq, client.cafile_.c_str(), NULL, client.certfile_.c_str(), client.keyfile_.c_str(), NULL);

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);

    rc = mosquitto_connect(mosq, client.host_.c_str(), stoi(client.port_), 60);

    if (rc != MOSQ_ERR_SUCCESS)
    {
        log(__LINE__, rc, "Reconnecting ...");
        return -1;
    }

    while (1)
    {
        std::string str = "Hello from pub_client!";
        mosquitto_publish(mosq, NULL, client.topic_[0].c_str(), str.length(), str.c_str(), 1, true);

        std::string strTemp = temperatureCpu();
        mosquitto_publish(mosq, NULL, client.topic_[0].c_str(), strTemp.length(), strTemp.c_str(), 1, true);

        std::string strRamUsage = ramUsage();
        mosquitto_publish(mosq, NULL, client.topic_[0].c_str(), strRamUsage.length(), strRamUsage.c_str(), 1, true);

        std::string strCpuUsage = cpuUsage();
        mosquitto_publish(mosq, NULL, client.topic_[0].c_str(), strCpuUsage.length(), strCpuUsage.c_str(), 1, true);
        sleep(5);    
    }

    while(run == -1)
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
