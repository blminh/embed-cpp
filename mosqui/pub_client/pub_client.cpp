#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <signal.h>
#include <openssl/ssl.h>
#include <mosquitto.h>
#include <nlohmann/json.hpp>

static int run = -1;

void handle_sigint(int signal)
{
    std::cout << "Catch signal: " << signal << std::endl;
    run = 0;
    exit(1);
}

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
    if (rc != 0)
    {
        exit(1);
    }
}

void on_disconnect(struct mosquitto *mosq, void *obj, int rc)
{
    run = rc;
}

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
        return 1;
    }

    Client client = readConfig("config.json");

    mosquitto_tls_opts_set(mosq, 1, client.tlsVersion_.c_str(), NULL);
    mosquitto_tls_set(mosq, client.cafile_.c_str(), NULL, client.certfile_.c_str(), client.keyfile_.c_str(), NULL);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    rc = mosquitto_connect(mosq, client.host_.c_str(), stoi(client.port_), 60);

    std::string str = "Hello from pub_client!";
    int pub = mosquitto_publish(mosq, NULL, client.topic_[0].c_str(), 40, str.c_str(), 0, false);

    while (run == -1)
    {
        mosquitto_loop(mosq, -1, 1);
    }

    mosquitto_destroy(mosq);

    mosquitto_lib_cleanup();
    return run;
}
