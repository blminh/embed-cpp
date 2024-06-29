#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <openssl/ssl.h>
#include <iostream>
#include <string>

static int run = -1;

void handle_sigint(int signal)
{
    std::cout << "Catch signal: " << signal << std::endl;
    run = 0;
}

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
    std::cout << "rc: " << rc << std::endl;
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

int main(int argc, char *argv[])
{
    int rc;
    struct mosquitto *mosq = NULL;
    int port = 8883;

    mosquitto_lib_init();
    mosq = mosquitto_new("pub_client", true, NULL);
    if (mosq == NULL)
    {
        return 1;
    }
    mosquitto_tls_opts_set(mosq, 1, "tlsv1.2", NULL);
    mosquitto_tls_set(mosq, "ca.crt", NULL, "client.crt", "client.key", NULL);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    rc = mosquitto_connect(mosq, "neko-S451LA", port, 60);

    mosquitto_publish(mosq, NULL, "/abc", 20, "Hello from pub_client!", 0, false);

    signal(SIGINT, handle_sigint);

    while (run == -1)
    {
        mosquitto_loop(mosq, -1, 1);
    }

    mosquitto_destroy(mosq);

    mosquitto_lib_cleanup();
    return run;
}
