#include <iostream>
#include "includes/game.hpp"
#include "includes/player.hpp"

int main()
{
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    Game::Player player{playerName};
    std::cout << "Welcome to this game, " << player.getName() << ". \n";

    while (!player.isDead() && !player.hasWon())
        Game::fightMonster(player);

    if (player.isDead())
    {
        std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold. \n";
        std::cout << "Too bad you can't take it with you! \n";
    }
    else
    {
        std::cout << "You wont the game with " << player.getGold() << " gold. \n";
    }
    return 0;
}