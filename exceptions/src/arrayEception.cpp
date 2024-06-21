#include <cmath>
#include <iostream>
#include "../includes/ArrayException.hpp"

namespace user_exceptions
{
    ArrayException::ArrayException() {}
    ArrayException::ArrayException(std::string_view error) : mError_{error} {}

    const std::string &ArrayException::getError() const { return mError_; }

    const char *ArrayException::what() const noexcept
    {
        return mError_.c_str();
    }
};
