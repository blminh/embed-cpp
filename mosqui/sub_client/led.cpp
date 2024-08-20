#include <iostream>
#include <wiringPi.h>

int LED = 0;
bool reset = false;
void led(int status)
{
    std::cout << "Raspberry Pi blink" << std::endl;
    wiringPiSetup();
    pinMode(LED, OUTPUT);
    if (status == 1)
        digitalWrite(LED, HIGH);
    else
        digitalWrite(LED, LOW);
}
