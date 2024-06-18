#include <cmath>
#include <iostream>
#include "../includes/intArray.hpp"
#include "../includes/arrayException.hpp"

namespace user_exceptions
{
    // IntArray
    IntArray::IntArray() {}
    int IntArray::getLength() const { return 3; }

    int &IntArray::operator[](const int index)
    {
        if (index < 0 || index >= getLength())
            throw ArrayException("Invalid index");
        return mData_[index];
    }
};
