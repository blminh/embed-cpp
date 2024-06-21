#include <cmath>
#include <iostream>
#include "../includes/MoveClass.hpp"
#include "../includes/CopyClass.hpp"

namespace user_exceptions
{
    // Move class
    MoveClass::MoveClass(int resource) : mResource_{new int{resource}} {}

    // Copy constructor
    MoveClass::MoveClass(const MoveClass &that)
    {
        if (that.mResource_ != nullptr)
        {
            mResource_ = new int{*that.mResource_};
        }
    }

    // Move constructor
    MoveClass::MoveClass(MoveClass &&that) noexcept : mResource_{that.mResource_}
    {
        that.mResource_ = nullptr;
    }
    MoveClass::~MoveClass()
    {
        std::cout << "destroying " << *this << std::endl;
        delete mResource_;
    }

    std::ostream &operator<<(std::ostream &out, const MoveClass &moveClass)
    {
        out << "MoveClass(";
        if (moveClass.mResource_ == nullptr)
        {
            out << "empty";
        }
        else
        {
            out << *moveClass.mResource_;
        }

        out << ")";
        return out;
    }
};
