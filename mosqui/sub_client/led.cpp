#include <iostream>
#include <wiringPi.h>

void led(int status)
{
    std::cout << "Raspberry Pi blink" << std::endl;
    std::cout << "Status: " << status << std::endl;

    wiringPiSetup();

    int LED = 2;
    pinMode(LED, OUTPUT);

    if (status == 1)
        digitalWrite(LED, HIGH);
    else
        digitalWrite(LED, LOW);
}
