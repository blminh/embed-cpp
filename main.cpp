#include "./includes/foo.h"
#include "./includes/todo.h"

int main()
{
    // foo_file::foo();
    std::cout << "Starting main()\n";

    // foo_file::doA();
    // todo_file::doA();
    // todo_file::doB();
    double towerHeight{getTowerHeight()};
    int seconds {0};
    while (calAndPrintBallHeight(towerHeight, seconds) > 0.0)
    {
        ++seconds;
    }
    

    std::cout << "Ending main()\n";

    return 0;
}