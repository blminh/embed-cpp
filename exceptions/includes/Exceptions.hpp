#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <cmath>

namespace user_exceptions
{
    class Exceptions
    {
    private:
    public:
        Exceptions();
        ~Exceptions();

        double mySqrt(double value);
    };
};

#endif