#include <iostream>
#include <wiringPi.h>

void led(int pin, int status)
{
    std::cout << "Raspberry Pi blink" << std::endl;

    if (wiringPiSetup() == -1)
    {
        std::cout << "Fail to setup wiringPi!!!" << std::endl;
        throw;
    }

    pinMode(pin, OUTPUT);

    if (status == 1)
        digitalWrite(pin, HIGH);
    else
        digitalWrite(pin, LOW);
}
