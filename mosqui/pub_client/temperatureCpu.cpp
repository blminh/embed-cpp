#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

std::string temperatureCpu()
{
    std::string tempCpu = "";
    std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
    if (!file)
    {
        std::cerr << "Error opening file" << std::endl;
        throw "Error opening file";
    }

    int temp;
    file >> temp;

    tempCpu = "Cpu temperature: " + std::to_string(temp / 1000) + "°C";
    std::cout << tempCpu << std::endl;
    file.close();

    return tempCpu;
}