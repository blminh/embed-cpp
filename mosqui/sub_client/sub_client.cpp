#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mosquitto.h>
#include <iostream>
#include <string>
#include <csignal>

static int run = -1;

void handle_sigint(int signal)
{
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
    std::cout << "Subscriber sub_client received message of topic: " << message->topic << " | Data: " << reinterpret_cast<char *>(message->payload) << "\n";
    return 0;
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

    libmosquitto_tls *tls;
    snprintf(tls->cafile, sizeof("ca.crt") + 1, "%s", "ca.crt");
    tls->capath = NULL;
    snprintf(tls->certfile, sizeof("client.crt") + 1, "%s", "client.crt");
    snprintf(tls->keyfile, sizeof("client.key") + 1, "%s", "client.key");
    tls->ciphers = NULL;
    tls->cert_reqs = 0;
    snprintf(tls->tls_version, sizeof("tlsv1.2") + 1, "%s", "tlsv1.2");
    tls->pw_callback = NULL;

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

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_lib_cleanup();
    return run;
}
