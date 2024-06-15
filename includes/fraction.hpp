#pragma once
#ifndef __FRACTION_H__
#define __FRACTION_H__

#include <iostream>

namespace fraction
{
    class Fraction
    {
    private:
        int m_numerator{0};
        int m_denominator{1};

    public:
        Fraction(int numerator, int denominator);
        friend std::ostream &operator<<(std::ostream &out, const Fraction &frac);
    };

    void fraction();
}

#endif