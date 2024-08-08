#include <mosquittopp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* for sleep() */

void on_connect(struct mosquitto *mosq, void *obj, int reason_code)
{
    printf("on_connect: %s\n", mosquitto_connack_string(reason_code));
    if (reason_code != 0)
    {
        mosquitto_disconnect(mosq);
    }
}
void on_publish(struct mosquitto *mosq, void *obj, int mid)
{
    printf("Message with mid %d has been published.\n", mid);
}

int get_temperature()
{
    sleep(1);
    return random() % 100;
}
void publish_sensor_data(struct mosquitto *mosq)
{
    char payload[20];
    int temp;
    int rc;

    temp = get_temperature();
    snprintf(payload, sizeof(payload), "%d", temp);

    rc = mosquitto_publish(mosq, NULL, "home", strlen(payload), payload, 2, true);
    if (rc != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Error publishing: %s\n", mosquitto_strerror(rc));
    }
}
void sendToSystem()
{
    struct mosquitto *mosq;
    int rc;

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (mosq == NULL)
    {
        fprintf(stderr, "Error: Out of memory.\n");
        return;
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_publish_callback_set(mosq, on_publish);

    rc = mosquitto_connect(mosq, "0.0.0.0", 1883, 60);
    if (rc != MOSQ_ERR_SUCCESS)
    {
        mosquitto_destroy(mosq);
        fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
        return;
    }

    /* Run the network loop in a background thread, this call returns quickly. */
    rc = mosquitto_loop_start(mosq);
    if (rc != MOSQ_ERR_SUCCESS)
    {
        mosquitto_destroy(mosq);
        fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
        return;
    }

    while (1)
    {
        publish_sensor_data(mosq);
    }

    mosquitto_lib_cleanup();
}
