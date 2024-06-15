#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>
#include <string_view>
#include <exception>

namespace user_exceptions
{
    class Exceptions
    {
    private:
    public:
        Exceptions();
        ~Exceptions();

        double mySqrt(double x);
        void doExceptions();
    };

    class ArrayException : public std::exception
    {
    private:
        std::string m_error{};

    public:
        ArrayException(std::string_view error);
        const std::string &getError() const;
        const char *what() const noexcept override;
    };

    class IntArray
    {
    private:
        int m_data[3]{};

    public:
        IntArray();

        int getLength() const;
        int &operator[](const int index);
    };
};

#endif