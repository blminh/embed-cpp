#include "todo.h"

namespace todo_file
{
    void doB()
    {
        std::cout << "In doB()\n";
    }

    void doA()
    {
        std::cout << "In doA() in todo file\n";

        doB();
    }
}