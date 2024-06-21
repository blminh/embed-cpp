#ifndef __FRACTION_H__
#define __FRACTION_H__

#include <iostream>

class Fraction
{
private:
    int mNumerator_{0};
    int mDenominator_{1};

public:
    Fraction(int numerator, int denominator);
    friend std::ostream &operator<<(std::ostream &out, const Fraction &frac);
};

#endif