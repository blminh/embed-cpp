#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>
#include <string_view>
#include <exception>
#include <utility>
#include <stdexcept>

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

    // Array Exception
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

    void arrayExceptionAction();

    // The move constructors exception problem
    class MoveClass
    {
    private:
    private:
        int *m_resource{};

    public:
        MoveClass() = default;
        MoveClass(int resource);
        // Copy constructor
        MoveClass(const MoveClass &that);
        // Move constructor
        MoveClass(MoveClass &&that) noexcept;
        ~MoveClass();

        friend std::ostream &operator<<(std::ostream &out, const MoveClass &moveClass);
    };

    class CopyClass
    {
    public:
        bool m_throw{};
        CopyClass() = default;
        CopyClass(const CopyClass &that);
    };

    void moveClassAction();
};

#endif