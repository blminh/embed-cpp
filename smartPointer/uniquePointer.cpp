#include <iostream>
#include "UniquePointer.hpp"

int main()
{
    UniquePointer uPtr{0};
    uPtr.show();
    uPtr = 10;
    uPtr.show();

    return 0;
}