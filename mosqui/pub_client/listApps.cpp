#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

struct DataProcess
{
    int id;
    std::string name;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataProcess, id, name)
};

std::string listRunningProcesses()
{
    struct dirent *entry;
    DIR *dp = opendir("/proc");

    if (dp == nullptr)
    {
        std::cerr << "Failed to open /proc directory." << std::endl;
        return {};
    }

    std::vector<DataProcess> listData = {};
    while ((entry = readdir(dp)))
    {
        if (entry->d_type == DT_DIR)
        {
            char *endptr;
            long pid = strtol(entry->d_name, &endptr, 10);
            if (*endptr == '\0')
            { // Valid process ID
                std::string path = "/proc/" + std::string(entry->d_name) + "/comm";
                std::ifstream file(path);
                if (file)
                {
                    std::string name;
                    getline(file, name);
                    // std::cout << "Process ID: " << pid << " | Process Name: " << name << std::endl;
                    DataProcess dps;
                    dps.id = pid;
                    dps.name = name;
                    // std::cout << "ID: " << dps.id << " | Name: " << dps.name << std::endl;
                    listData.push_back(dps);
                }
            }
        }
    }

    closedir(dp);
    // std::cout << "Size: " << listData.size() << std::endl;
    // for (auto i = listData.begin(); i < listData.end(); i++)
    // {
    //     std::cout << i->id << std::endl;
    // }
    nlohmann::json list = listData;
    return list.dump();
}

// int main()
// {
//     nlohmann::json list = listRunningProcesses();
//     std::cout << list << std::endl;
//     // for (auto i = list.begin(); i < list.end(); i++)
//     // {
//     //     std::cout << "ID: " << i->id << " | Name: " << i->name << std::endl;
//     // }
//     // listRunningProcesses();

//     return 0;
// }