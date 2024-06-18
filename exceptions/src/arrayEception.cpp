#include <cmath>
#include <iostream>
#include "../includes/arrayException.hpp"
#include "../includes/intArray.hpp"

namespace user_exceptions
{
    ArrayException::ArrayException() {}
    ArrayException::ArrayException(std::string_view error) : mError_{error} {}

    const std::string &ArrayException::getError() const { return mError_; }

    const char *ArrayException::what() const noexcept
    {
        return mError_.c_str();
    }

    void ArrayException::arrayExceptionAction()
    {
        IntArray array;

        // try
        // {
        //     int value{array[5]}; // out of range subscript
        // }
        // catch (const ArrayException &exception)
        // {
        //     std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
        // }

        try
        {
            int value{array[4]};
        }
        catch (const user_exceptions::ArrayException &exception)
        {
            std::cerr << "An array exception occurred (" << exception.what() << ")\n";
        }
        catch (const std::exception &exception)
        {
            std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
        }
    }
};
