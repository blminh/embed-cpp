#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <mutex>
#include <mosquitto.h>
#include <signal.h>
#include <nlohmann/json.hpp>

#define DEL_PTR(ptr)    \
    if (ptr != nullptr) \
    {                   \
        delete[] ptr;   \
        ptr = nullptr;  \
    }

static int run = -1;
std::mutex mutex;

void handle_sigint(int signal)
{
    std::cout << "Catch signal: " << signal << std::endl;
    {
        std::lock_guard<std::mutex> lock(mutex);
        run = 0;
    }
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
    std::lock_guard<std::mutex> lock(mutex);
    run = rc;
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
    std::vector<std::string> topic_;
};

Client readConfig(std::string filepath)
{
    try
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
    catch (nlohmann::json::exception e)
    {
        std::cout << "Line: " << __LINE__ << "| Error: " << e.what() << std::endl;
        throw std::runtime_error(e.what());
    }
    catch (std::exception e)
    {
        std::cout << "Line: " << __LINE__ << "| Error: " << e.what() << std::endl;
        throw std::runtime_error(e.what());
    }
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
        return -1;
    }

    Client client = readConfig("config.json");

    libmosquitto_tls tls;
    int sizeCafile = client.cafile_.length() + 1;
    tls.cafile = new char[sizeCafile];
    snprintf(tls.cafile, sizeCafile, "%s", client.cafile_.c_str());

    tls.capath = NULL;

    int sizeCertfile = client.certfile_.length() + 1;
    tls.certfile = new char[sizeCertfile];
    snprintf(tls.certfile, sizeCertfile, "%s", client.certfile_.c_str());

    int sizeKeyfile = client.keyfile_.length() + 1;
    tls.keyfile = new char[sizeKeyfile];
    snprintf(tls.keyfile, sizeKeyfile, "%s", client.keyfile_.c_str());

    tls.cert_reqs = 0;
    tls.ciphers = NULL;
    tls.pw_callback = NULL;

    int sizeTlsVersion = client.tlsVersion_.length() + 1;
    tls.tls_version = new char[sizeTlsVersion];
    snprintf(tls.tls_version, sizeTlsVersion, "%s", client.tlsVersion_.c_str());

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);

    std::cout << "Topic: " << client.topic_[0].c_str() << std::endl;
    std::cout << "Topic: " << client.topic_[1].c_str() << std::endl;

    mosquitto_subscribe_callback(
        on_message_callback,
        NULL,
        client.topic_[0].c_str(),
        0,
        client.host_.c_str(),
        stoi(client.port_),
        "sub_client",
        60,
        true,
        NULL, NULL, NULL,
        &tls);

    DEL_PTR(tls.cafile)
    DEL_PTR(tls.certfile)
    DEL_PTR(tls.keyfile)
    DEL_PTR(tls.tls_version)

    // mosquitto_loop_forever(mosq, run, 1);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return run;
}
