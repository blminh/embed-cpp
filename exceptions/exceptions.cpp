#include <cmath>
#include <iostream>
#include "includes/exceptions.hpp"
#include "includes/arrayException.hpp"
#include "includes/intArray.hpp"
#include "includes/moveClass.hpp"
#include "includes/copyClass.hpp"

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
    ArrayException::ArrayException() {}
    ArrayException::ArrayException(std::string_view error) : mError_{error} {}

    const std::string &ArrayException::getError() const { return mError_; }

    const char *ArrayException::what() const noexcept
    {
        return mError_.c_str();
    }

    // IntArray
    IntArray::IntArray() {}
    int IntArray::getLength() const { return 3; }

    int &IntArray::operator[](const int index)
    {
        if (index < 0 || index >= getLength())
            throw ArrayException("Invalid index");
        return mData_[index];
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

    // Move class
    MoveClass::MoveClass(int resource) : mResource_{new int{resource}} {}

    // Copy constructor
    MoveClass::MoveClass(const MoveClass &that)
    {
        if (that.mResource_ != nullptr)
        {
            mResource_ = new int{*that.mResource_};
        }
    }

    // Move constructor
    MoveClass::MoveClass(MoveClass &&that) noexcept : mResource_{that.mResource_}
    {
        that.mResource_ = nullptr;
    }
    MoveClass::~MoveClass()
    {
        std::cout << "destroying " << *this << std::endl;
        delete mResource_;
    }

    std::ostream &operator<<(std::ostream &out, const MoveClass &moveClass)
    {
        out << "MoveClass(";
        if (moveClass.mResource_ == nullptr)
        {
            out << "empty";
        }
        else
        {
            out << *moveClass.mResource_;
        }

        out << ")";
        return out;
    }

    // Copy class
    CopyClass::CopyClass(const CopyClass &that) : pubThrow_{that.pubThrow_}
    {
        if (pubThrow_)
        {
            throw std::runtime_error{"abort"};
        }
    }

    void MoveClass::moveClassAction()
    {
        // We can make a std::pair without any problems:
        std::pair my_pair{MoveClass{13}, CopyClass{}};

        std::cout << "my_pair.first: " << my_pair.first << '\n';

        // But the problem arises when we try to move that pair into another pair.
        try
        {
            my_pair.second.pubThrow_ = true; // To trigger copy constructor exception

            // The following line will throw an exception
            // std::pair moved_pair{std::move(my_pair)}; // We'll comment out this line later
            std::pair moved_pair{std::move_if_noexcept(my_pair)}; // We'll uncomment this line later

            std::cout << "moved pair exists\n"; // Never prints
        }
        catch (const std::exception &ex)
        {
            std::cerr << "Error found: " << ex.what() << '\n';
        }

        std::cout << "my_pair.first: " << my_pair.first << '\n';
    }
};
