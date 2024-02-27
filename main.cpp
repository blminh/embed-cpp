#include "foo.h"
#include "todo.h"

int main()
{
    foo();
    std::cout << "Starting main()\n";

    doA();
    doB();

    std::cout << "Ending main()\n";

    return 0;
}