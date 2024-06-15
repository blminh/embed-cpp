#include <cmath>
#include <iostream>
#include "../includes/exceptions.hpp"

namespace user_exceptions
{
    Exceptions::Exceptions() {}
    Exceptions::~Exceptions() {}

    double Exceptions::mySqrt(double x)
    {
        // If the user entered a negative number, this is an error condition
        if (x < 0.0)
            throw "Can not take sqrt of negative number"; // throw exception of type const char*

        return std::sqrt(x);
    }

    void Exceptions::doExceptions()
    {
        std::cout << "Enter a number: ";
        double x{};
        std::cin >> x;

        try // Look for exceptions that occur within try block and route to attached catch block(s)
        {
            double d = mySqrt(x);
            std::cout << "The sqrt of " << x << " is " << d << '\n';
        }
        catch (const char *exception) // catch exceptions of type const char*
        {
            std::cerr << "Error: " << exception << std::endl;
        }
        catch (...) // catch-all handler
        {
            std::cout << "We caught an exception of an undetermined type\n";
        }
    }

    // ArrayException
    ArrayException::ArrayException(std::string_view error) : m_error{error} {}

    const std::string &ArrayException::getError() const { return m_error; }
    const char *ArrayException::what() const noexcept
    {
        return m_error.c_str();
    }

    // IntArray
    IntArray::IntArray() {}
    int IntArray::getLength() const { return 3; }

    int &IntArray::operator[](const int index)
    {
        if (index < 0 || index >= getLength())
            throw ArrayException("Invalid index");
        return m_data[index];
    }
};
