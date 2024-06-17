#ifndef __ARRAY_EXCEPTIONS_H__
#define __ARRAY_EXCEPTIONS_H__

#include <string>
#include <string_view>
#include <exception>

namespace user_exceptions
{
    class ArrayException : public std::exception
    {
    private:
        std::string mError_{};

    public:
        ArrayException();
        ArrayException(std::string_view error);
        const std::string &getError() const;
        const char *what() const noexcept override;

        void arrayExceptionAction();
    };
};

#endif