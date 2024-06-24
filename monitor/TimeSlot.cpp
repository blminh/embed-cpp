#include "TimeSlot.hpp"
#include <iostream>
#include <chrono>

TimeSlot::TimeSlot(int timeOn, std::function<void()> cb) : mCb_{cb}
{
    std::cout << "Constructor" << std::endl;
    auto start{std::chrono::steady_clock::now()};
    std::cout << "Start: " << std::endl;
    // mTimeAt_ = timeOn + ???;
}

TimeSlot::~TimeSlot()
{
    std::cout << "Destructor" << std::endl;
}