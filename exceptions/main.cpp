#include "includes/Exceptions.hpp"
#include "includes/ArrayException.hpp"
#include "includes/IntArray.hpp"
#include "includes/MoveClass.hpp"
#include "includes/CopyClass.hpp"

int main()
{
    // >>> Exceptions:
    user_exceptions::Exceptions exc;
    std::cout << "Enter a number: ";
    double x{};
    std::cin >> x;

    try
    {
        double d = exc.mySqrt(x);
        std::cout << "The sqrt of " << x << " is " << d << '\n';
    }
    catch (const char *exception)
    {
        std::cerr << "Error: " << exception << std::endl;
    }
    catch (...) // catch-all handler
    {
        std::cout << "We caught an exception of an undetermined type\n";
    }

    // >>> Array exception:
    // user_exceptions::IntArray array;
    // try
    // {
    //     int value{array[4]};
    // }
    // catch (const user_exceptions::ArrayException &exception)
    // {
    //     std::cerr << "An array exception occurred (" << exception.what() << ")\n";
    // }
    // catch (const std::exception &exception)
    // {
    //     std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
    // }

    // >>> MoveClass:
    // std::pair my_pair{user_exceptions::MoveClass{13}, user_exceptions::CopyClass{}};

    // std::cout << "my_pair.first: " << my_pair.first << '\n';

    // try
    // {
    //     my_pair.second.pubThrow_ = true;

    //     // std::pair moved_pair{std::move(my_pair)}; //comment out this line later
    //     std::pair moved_pair{std::move_if_noexcept(my_pair)}; // uncomment this line later

    //     std::cout << "moved pair exists\n"; // Never prints
    // }
    // catch (const std::exception &ex)
    // {
    //     std::cerr << "Error found: " << ex.what() << '\n';
    // }

    // std::cout << "my_pair.first: " << my_pair.first << '\n';

    return 0;
}