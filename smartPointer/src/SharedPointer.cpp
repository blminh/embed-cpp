#include <iostream>
#include "SharedPointer.hpp"

SharedPointer::SharedPointer()
{
    // mPtr_ = new int(0);
    // mCounter_ = new int(1);
    // std::cout << "Constructor" << std::endl;
}

SharedPointer::SharedPointer(int *ptr = nullptr)
{
    mPtr_ = ptr;
    mCounter_ = new int(1);
    std::cout << "Constructor" << std::endl;
}

SharedPointer::SharedPointer(const SharedPointer &sPtr)
{
    mPtr_ = sPtr.mPtr_;
    mCounter_ = sPtr.mCounter_;
    (*mCounter_)++;
}

SharedPointer::~SharedPointer()
{
    (*mCounter_)--;
    if (*mCounter_ == 0)
    {
        delete mPtr_;
        delete mCounter_;
    }

    std::cout << "Destructor" << std::endl;
}

SharedPointer &SharedPointer::operator=(const SharedPointer &sPtr)
{
    std::cout << "Assignment!" << std::endl;
    if (mPtr_ != sPtr.mPtr_)
    {
        if (mPtr_ && mCounter_)
        {
            *mCounter_--;
            if (*mCounter_ == 0)
            {
                delete mPtr_;
                delete mCounter_;
            }
        }
        mPtr_ = sPtr.mPtr_;
        if (mPtr_)
        {
            mCounter_ = sPtr.mCounter_;
            (*mCounter_)++;
        }
    }

    return *this;
}

void SharedPointer::show()
{
    std::cout << "Value: " << *mPtr_ << std::endl;
}
