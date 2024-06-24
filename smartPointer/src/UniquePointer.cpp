#include <iostream>
#include "UniquePointer.hpp"

UniquePointer::UniquePointer()
{
    mPtr_ = new int(0);
    std::cout << "Constructor unique pointer." << std::endl;
}

UniquePointer::UniquePointer(int val)
{
    mPtr_ = new int(val);
    std::cout << "Constructor unique pointer." << std::endl;
}

UniquePointer::~UniquePointer()
{
    delete mPtr_;
    std::cout << "Destructor unique pointer." << std::endl;
}

UniquePointer &UniquePointer::operator=(const UniquePointer &uPtr)
{
    std::cout << "Assignment!" << std::endl;
    *mPtr_ = *uPtr.mPtr_;
    return *this;
}

void UniquePointer::show()
{
    std::cout << "Value: " << *mPtr_ << std::endl;
}