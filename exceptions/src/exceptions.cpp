#include <iostream>
#include "../includes/Exceptions.hpp"

namespace user_exceptions
{
    Exceptions::Exceptions() {}
    Exceptions::~Exceptions() {}

    double Exceptions::mySqrt(double x)
    {
        if (x < 0.0)
            throw "Can not take sqrt of negative number";

        return std::sqrt(x);
    }
};
