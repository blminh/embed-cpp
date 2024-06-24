#include <cmath>
#include <iostream>
#include "../includes/IntArray.hpp"
#include "../includes/ArrayException.hpp"

namespace user_exceptions
{
    IntArray::IntArray() {}
    int IntArray::getLength() const { return 3; }

    int &IntArray::operator[](const int index)
    {
        if (index < 0 || index >= getLength())
            throw ArrayException("Invalid index");
        return mData_[index];
    }
};
