#include <iostream>
#include <sstream>
#include "../includes/game.hpp"
#include "../includes/potion.hpp"
#include "../includes/monster.hpp"
#include "../includes/player.hpp"

namespace Game
{
    void onMonsterKilled(Player &player, const Monster &monster)
    {
        std::cout << "You killed the " << monster.getName() << ". \n";
        player.levelUp();
        std::cout << "You are now level " << player.getLevel() << ". \n";
        std::cout << "You found " << monster.getGold() << " gold. \n";
        // std::cout << "You killed the " << monster.getName() << ".\n";
        // player.levelUp();
        // std::cout << "You are now level " << player.getLevel() << ".\n";
        // std::cout << "You found " << monster.getGold() << " gold.\n";
        // player.addGold(monster.getGold());

        // 30% chance of finding a potion
        constexpr int potionChance{30};
        if (Random::get(1, 100) <= potionChance)
        {
            auto potion{Potion::getRandomPotion()};

            std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
            char choice{};
            std::cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                player.drinkPotion(potion);
                std::cout << "You drank a " << potion.getName() << ".\n";
            }
        }
    }

    void attackMonster(Player &player, Monster &monster)
    {
        if (player.isDead())
            return;

        std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage. \n";

        monster.reduceHealth(player.getDamage());

        if (monster.isDead())
        {
            onMonsterKilled(player, monster);
        }
    }

    void attackPlayer(Player &player, const Monster &monster)
    {
        if (monster.isDead())
            return;

        player.reduceHealth(monster.getDamage());
        std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage. \n";
    }

    void fightMonster(Player &player)
    {
        Monster monster{Monster::getRandomMonster()};
        std::cout << "You have encountered a " << monster.getName() << std::endl;
        std::cout << "++ Your health: " << player.getHealth() << ", damage: " << player.getDamage() << " ++. \n";
        std::cout << "++ " << monster.getName() << " health: " << monster.getHealth() << ", damage: " << monster.getDamage() << " ++. \n";

        while (!monster.isDead() && !player.isDead())
        {
            std::cout << "(R) Run or (F) Fight: ";
            char input{};
            std::cin >> input;

            switch (input)
            {
            case 'R':
            case 'r':
                if (Random::get(1, 2) == 1)
                {
                    std::cout << "You successfully fled. \n";
                    return;
                }
                else
                {
                    std::cout << "You failed to flee. \n";
                    attackPlayer(player, monster);
                    continue;
                }
                break;
            case 'F':
            case 'f':
                attackMonster(player, monster);
                attackPlayer(player, monster);
                break;

            default:
                break;
            }
        }
    }
};
