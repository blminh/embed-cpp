#include <iostream>
#include <wiringPi.h>
#include <lcd.h>
#include <softPwm.h>
#include <string>
#include <mutex>

#define LCD_RS 0        // GPIO17
#define LCD_E 1         // GPIO27
#define LCD_D4 2        // GPIO22
#define LCD_D5 3        // GPIO23
#define LCD_D6 4        // GPIO24
#define LCD_D7 5        // GPIO25
#define LCD_BACKLIGHT 6 // GPIO6

std::mutex mtx_;
std::string text_ = "- Raspberry Pi -";

void syncData(std::string msg)
{
    std::cout << "syncData | Msg: " << msg << std::endl;
    std::lock_guard<std::mutex> lock(mtx_);
    if (msg.length() == 0)
    {
        text_ = "- Raspberry Pi -";
    }
    else
    {
        text_ = msg;
    }
}

void showLCD16()
{
    wiringPiSetup();

    int lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

    if (lcd == -1)
    {
        std::cout << "LCD initialization failed!\n";
        throw;
    }

    pinMode(LCD_BACKLIGHT, OUTPUT);
    digitalWrite(LCD_BACKLIGHT, 30);

    lcdClear(lcd);
    lcdPosition(lcd, 0, 0);

    std::string cpText = text_;

    do
    {
        int strLen = cpText.length();
        int strDiv = strLen;
        if (strLen > 16)
            strDiv = strLen - 16;

        lcdPuts(lcd, cpText.c_str());
        delay(300);
        lcdClear(lcd);

        cpText = cpText.substr(1, strLen);
        strDiv--;
        if (strDiv == 0)
        {
            cpText = text_;
        }
    } while (1);

    lcdPosition(lcd, 0, 1);
    lcdPuts(lcd, "- Raspberry Pi -");

    lcdClear(lcd);
    softPwmCreate(LCD_BACKLIGHT, 0, 0);
}
