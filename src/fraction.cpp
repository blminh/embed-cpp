#include <stdexcept>
#include <exception>
#include "../includes/Fraction.hpp"

Fraction::Fraction(int numerator = 0, int denominator = 1) : mNumerator_{numerator}, mDenominator_{denominator}
{
    if (mDenominator_ == 0)
    {
        throw std::runtime_error("Invalid denominator! \n");
    }
}

std::ostream &operator<<(std::ostream &out, const Fraction &frac)
{
    out << frac.mNumerator_ << "/" << frac.mDenominator_;
    return out;
}