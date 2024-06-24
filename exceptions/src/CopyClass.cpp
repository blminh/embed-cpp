#include <cmath>
#include <iostream>
#include "../includes/CopyClass.hpp"

namespace user_exceptions
{
    CopyClass::CopyClass(const CopyClass &that) : pubThrow_{that.pubThrow_}
    {
        if (pubThrow_)
        {
            throw std::runtime_error{"abort"};
        }
    }
};
