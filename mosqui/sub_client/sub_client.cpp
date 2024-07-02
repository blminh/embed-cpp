#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mosquitto.h>
#include <iostream>
#include <string>
#include <csignal>
#include <fstream>
#include <nlohmann/json.hpp>
#include <signal.h>

static int run = -1;

void handle_sigint(int signal)
{
    std::cout << "Catch signal: " << signal << std::endl;
    run = 0;
}

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
    if (rc)
    {
        exit(1);
    }
    else
    {
        mosquitto_disconnect(mosq);
    }
}

void on_disconnect(struct mosquitto *mosq, void *obj, int rc)
{
    run = rc;
}

void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos)
{
    mosquitto_disconnect(mosq);
}

int on_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    std::cout << "----- Message -----" << std::endl;
    std::cout << "Subscriber sub_client received message of topic: " << message->topic << " | Data: " << reinterpret_cast<char *>(message->payload) << "\n";
    return 0;
}

struct Client
{
    std::string cafile_;
    std::string certfile_;
    std::string keyfile_;
    std::string tlsVersion_;
    std::string host_;
    std::string port_;
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
    return client;
}

int main(int argc, char *argv[])
{
    int rc;
    struct mosquitto *mosq = NULL;
    int port = 8883;

    mosquitto_lib_init();

    mosq = mosquitto_new("sub_client", true, NULL);
    if (mosq == NULL)
    {
        return 1;
    }

    // Client client = readConfig("config.json");
    // std::cout << client.cafile_ << std::endl;
    // std::cout << client.certfile_ << std::endl;
    // std::cout << client.keyfile_ << std::endl;
    // std::cout << client.tlsVersion_ << std::endl;
    // std::cout << client.host_ << std::endl;
    // std::cout << client.port_ << std::endl;
    // std::cout << "Field: " << cafile_ << "| Type: " << typeid(cafile_).name() << std::endl;

    std::ifstream conf("config.json");
    nlohmann::json confJson = nlohmann::json::parse(conf);
    std::string cafile_ = confJson["ca_file"];

    libmosquitto_tls *tls;
    snprintf(tls->cafile, sizeof(cafile_) + 1, "%s", cafile_.c_str());
    tls->capath = NULL;
    snprintf(tls->certfile, sizeof("client.crt") + 1, "%s", "client.crt");
    snprintf(tls->keyfile, sizeof("client.key") + 1, "%s", "client.key");
    tls->cert_reqs = 0;
    tls->ciphers = NULL;
    tls->pw_callback = NULL;
    snprintf(tls->tls_version, sizeof("tlsv1.2") + 1, "%s", "tlsv1.2");
    signal(SIGINT, handle_sigint);

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_subscribe_callback_set(mosq, on_subscribe);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);

    mosquitto_subscribe_callback(
        on_message_callback,
        NULL,
        "/abc",
        0,
        "neko-S451LA",
        8883,
        "sub_client",
        60,
        true,
        NULL, NULL, NULL,
        tls);

    mosquitto_loop_forever(mosq, run, 1);

    mosquitto_lib_cleanup();
    return run;
}
