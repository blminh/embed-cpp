#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <vector>

bool isNumber(const std::string &str)
{
    for (char ch : str)
    {
        if (!isdigit(ch))
            return false;
    }
    return true;
}

void getCpu(int &totalJiffies, int &workJiffies)
{
    std::ifstream statFile("/proc/stat");
    if (!statFile)
    {
        std::cerr << "Error opening /proc/stat file" << std::endl;
        throw;
    }

    std::string line;
    std::getline(statFile, line);
    std::istringstream iss(line);
    std::string token;
    std::vector<int> tokens;

    while (std::getline(iss, token, ' '))
    {
        if (!isNumber(token) || token.length() == 0)
        {
            continue;
        }
        tokens.push_back(stoi(token));
        totalJiffies += stoi(token);
    }

    workJiffies = tokens[0] + tokens[1] + tokens[2];
}

std::string cpuUsage()
{
    int totalJiffiesStart{0}, workJiffiesStart{0};
    getCpu(totalJiffiesStart, workJiffiesStart);
    sleep(1);
    int totalJiffiesEnd{0}, workJiffiesEnd{0};
    getCpu(totalJiffiesEnd, workJiffiesEnd);

    int totalJiffies = totalJiffiesEnd - totalJiffiesStart;
    int workJiffies = workJiffiesEnd - workJiffiesStart;

    double cpuUsage = (double)workJiffies / (double)totalJiffies * 100;
    std::cout << "cpu usage: " << cpuUsage << "%" << std::endl;
    std::string result = "CPU usage: " + std::to_string(cpuUsage) + "%";

    return result;
}
