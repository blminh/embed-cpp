#include <stdexcept>
#include <exception>
#include "../includes/fraction.hpp"

namespace fraction
{
    Fraction::Fraction(int numerator = 0, int denominator = 1) : m_numerator{numerator}, m_denominator{denominator}
    {
        if (m_denominator == 0)
        {
            throw std::runtime_error("Invalid denominator! \n");
        }
    }

    std::ostream &operator<<(std::ostream &out, const Fraction &frac)
    {
        out << frac.m_numerator << "/" << frac.m_denominator;
        return out;
    }

    void fraction()
    {
        std::cout << "Enter the numerator: ";
        int numerator{};
        std::cin >> numerator;

        std::cout << "Enter the denominator: ";
        int denominator{};
        std::cin >> denominator;

        try
        {
            Fraction f{numerator, denominator};
            std::cout << "Your fraction is: " << f << '\n';
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}