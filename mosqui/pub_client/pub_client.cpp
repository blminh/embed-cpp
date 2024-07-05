#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <openssl/ssl.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>
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
    if (rc == 0)
    {
        exit(1);
    }
}

void on_disconnect(struct mosquitto *mosq, void *obj, int rc)
{
    run = rc;
}

bool check(int val)
{
    if (val % 10 == 0)
        return true;
    return false;
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
    std::cout << confJson << std::endl;

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

void showLog(int line, std::string msg)
{
    std::cout << "Line: " << line << " | Log: " << msg << std::endl;
}

int main(int argc, char *argv[])
{
    int rc;
    struct mosquitto *mosq = NULL;
    int port = 8883;

    signal(SIGINT, handle_sigint);

    mosquitto_lib_init();
    mosq = mosquitto_new("pub_client", true, NULL);
    if (mosq == NULL)
    {
        return 1;
    }

    Client client = readConfig("config.json");

    int sizeTlsVersion = (client.tlsVersion_).length() + 1;
    char *tlsVersion = new char(sizeTlsVersion);
    snprintf(tlsVersion, sizeTlsVersion, "%s", client.tlsVersion_.c_str());

    int sizeCafile = (client.cafile_).length() + 1;
    char *cafile = new char(sizeCafile);
    snprintf(cafile, sizeCafile, "%s", client.cafile_.c_str());

    int sizeCertfile = (client.certfile_).length() + 1;
    char *certfile = new char(sizeCertfile);
    snprintf(certfile, sizeCertfile, "%s", client.certfile_.c_str());

    int sizeKeyfile = (client.keyfile_).length() + 1;
    char *keyfile = new char(sizeKeyfile);
    snprintf(keyfile, sizeKeyfile, "%s", client.keyfile_.c_str());

    int sizeHost = (client.host_).length() + 1;
    char *host = new char(sizeHost);
    snprintf(host, sizeHost, "%s", client.host_.c_str());

    mosquitto_tls_opts_set(mosq, 1, tlsVersion, NULL);
    mosquitto_tls_set(mosq, cafile, NULL, certfile, keyfile, NULL);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    rc = mosquitto_connect(mosq, host, 8883, 60);

    int counter{0};
    while (counter < 21)
    {
        if (check(counter))
        {
            std::string str = "Hello from pub_client! | Counter: " + std::to_string(counter);
            int pub = mosquitto_publish(mosq, NULL, client.topic_[0].c_str(), 40, str.c_str(), 0, false);
            std::cout << "Public message status: " << pub << std::endl;
        }
        std::cout << "Counter: " << counter << "| Check: " << check(counter) << std::endl;
        counter++;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    while (run == -1)
    {
        mosquitto_loop(mosq, -1, 1);
    }

    if (cafile != nullptr)
    {
        delete cafile;
        cafile = nullptr;
    }
    if (certfile != nullptr)
    {
        delete certfile;

        certfile = nullptr;
    }
    if (keyfile != nullptr)
    {
        delete keyfile;
        keyfile = nullptr;
    }
    if (tlsVersion != nullptr)
    {
        delete tlsVersion;
        tlsVersion = nullptr;
    }
    if (host != nullptr)
    {
        delete host;
        host = nullptr;
    }

    mosquitto_destroy(mosq);

    mosquitto_lib_cleanup();
    return run;
}
