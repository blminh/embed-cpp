#include "todo.hpp"

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

namespace constants
{
    constexpr double gravity{9.8};
}

double getTowerHeight()
{
    std::cout << "Enter the height of the tower: ";
    double towerHeight{};
    std::cin >> towerHeight;
    return towerHeight;
}

constexpr double calBallHeight(double towerHeight, int seconds)
{
    const double fallDistance{constants::gravity * (seconds * seconds) / 2.0};
    const double ballHeight{towerHeight - fallDistance};

    if (ballHeight < 0.0)
        return 0.0;
    return ballHeight;
}

void printBallHeight(double ballHeight, int seconds)
{
    if (ballHeight > 0.0)
        std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
    else
        std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

double calAndPrintBallHeight(double towerHeight, int seconds)
{
    double ballHeight{calBallHeight(towerHeight, seconds)};
    printBallHeight(ballHeight, seconds);

    return ballHeight;
}