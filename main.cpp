#include "./includes/foo.h"
#include "./includes/todo.h"

int main()
{
    foo_file::foo();
    std::cout << "Starting main()\n";

    foo_file::doA();
    todo_file::doA();
    todo_file::doB();

    std::cout << "Ending main()\n";

    return 0;
}