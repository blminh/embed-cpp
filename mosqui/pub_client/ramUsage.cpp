#include <fstream>
#include <iostream>

std::string ramUsage()
{
    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo)
    {
        std::cerr << "Error opening /proc/meminfo" << std::endl;
        throw "Error opening /proc/meminfo";
    }

    std::string line, strRamUsage;
    while (std::getline(meminfo, line))
    {
        size_t totalMem, freeMem;
        if (line.find("MemTotal") != std::string::npos)
        {
            size_t pos = line.find(":");
            if (pos != std::string::npos)
            {
                totalMem = std::stoul(line.substr(pos + 1));
            }
        }
        if (line.find("MemFree") != std::string::npos)
        {
            size_t pos = line.find(":");
            if (pos != std::string::npos)
            {
                freeMem = std::stoul(line.substr(pos + 1));
            }
        }
        size_t ramUsage = (totalMem - freeMem) * 100 / totalMem;
        std::cout << "Ram usage: " << ramUsage << "%" << std::endl;
        strRamUsage = "Ram usage: " + std::to_string(ramUsage) + "%";
    }

    meminfo.close();
    return strRamUsage;
}