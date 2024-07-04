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
    exit(1);
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

#include <vector>
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

    signal(SIGINT, handle_sigint);
    signal(SIGSEGV, handle_sigint);
    mosquitto_lib_init();

    mosq = mosquitto_new("sub_client", true, NULL);
    if (mosq == NULL)
    {
        return 1;
    }

    Client client = readConfig("config.json");
    for (auto topic : client.topic_)
    {
        std::cout << topic << " / ";
    }
    std::cout << std::endl;

    libmosquitto_tls tls;
    int sizeCafile = sizeof(client.cafile_) + 1;
    tls.cafile = new char(sizeCafile);
    snprintf(tls.cafile, sizeCafile, "%s", client.cafile_.c_str());

    tls.capath = NULL;

    int sizeCertfile = sizeof(client.certfile_) + 1;
    tls.certfile = new char(sizeCertfile);
    snprintf(tls.certfile, sizeCertfile, "%s", client.certfile_.c_str());

    int sizeKeyfile = sizeof(client.keyfile_) + 1;
    tls.keyfile = new char(sizeKeyfile);
    snprintf(tls.keyfile, sizeKeyfile, "%s", client.keyfile_.c_str());

    tls.cert_reqs = 0;
    tls.ciphers = NULL;
    tls.pw_callback = NULL;

    int sizeTlsVersion = sizeof(client.tlsVersion_) + 1;
    tls.tls_version = new char(sizeTlsVersion);
    snprintf(tls.tls_version, sizeTlsVersion, "%s", client.tlsVersion_.c_str());

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_subscribe_callback_set(mosq, on_subscribe);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);

    int sizeHost = sizeof(client.host_) + 1;
    char *host = new char(sizeHost);
    snprintf(host, sizeHost, "%s", client.host_.c_str());

    mosquitto_subscribe_callback(
        on_message_callback,
        NULL,
        "/abc",
        0,
        host,
        stoi(client.port_),
        "sub_client",
        60,
        true,
        NULL, NULL, NULL,
        &tls);

    delete host;
    delete tls.cafile;
    delete tls.keyfile;
    delete tls.certfile;
    delete tls.tls_version;

    mosquitto_loop_forever(mosq, run, 1);

    mosquitto_lib_cleanup();
    return run;
}
