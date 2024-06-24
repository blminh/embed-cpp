#include <iostream>
#include "SharedPointer.hpp"

int main()
{
    SharedPointer sPtr{new int(0)};
    sPtr.show();
    SharedPointer sPtr2 = sPtr;
    sPtr2.show();
    return 0;
}