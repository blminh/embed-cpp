#include <iostream>
#include <memory>
#include "Monitor.hpp"

Monitor::Monitor() : mValue_{0}
{
    std::cout << "Constructor" << std::endl;
}

Monitor::Monitor(int value, std::function<int(int, int)> cb) : mValue_{value}, cb_{cb}
{
}

Monitor::~Monitor()
{
    std::cout << "Destructor" << std::endl;
}

Monitor &Monitor::operator=(const int &value)
{
    std::cout << "Assignment" << std::endl;
    mValue_ = value;
    if (cb_)
    {
        auto result = std::bind(cb_, std::placeholders::_1, std::placeholders::_2);
        std::cout << result(10, value) << std::endl;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Monitor &monitor)
{
    out << monitor.mValue_ << std::endl;
    return out;
}
