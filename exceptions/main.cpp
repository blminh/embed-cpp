#include "includes/exceptions.hpp"
#include "includes/arrayException.hpp"
#include "includes/intArray.hpp"
#include "includes/moveClass.hpp"
#include "includes/copyClass.hpp"

int main()
{
    user_exceptions::Exceptions exc;
    exc.doExceptions();

    // user_exceptions::ArrayException arrExc;
    // arrExc.arrayExceptionAction();

    // user_exceptions::MoveClass moveClass;
    // moveClass.moveClassAction();
    return 0;
}