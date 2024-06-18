#include <cmath>
#include <iostream>
#include "../includes/moveClass.hpp"
#include "../includes/copyClass.hpp"

namespace user_exceptions
{
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
