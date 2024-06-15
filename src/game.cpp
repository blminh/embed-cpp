#include <iostream>
#include <sstream>
#include <array>
#include "../includes/game.hpp"

using namespace Game;

// Potion
Potion::Potion() {}
Potion::~Potion() {}
Potion::Potion(Potion::Type type, Potion::Size size) : m_type{type}, m_size{size} {}

Potion::Type Potion::getType() const
{
    return m_type;
}

Potion::Size Potion::getSize() const
{
    return m_size;
}

std::string_view Potion::getPotionTypeName(Potion::Type type)
{
    static constexpr std::string_view names[]{
        "Health",
        "Strength",
        "Poison",
    };
    return names[type];
}

std::string_view Potion::getPotionSizeName(Potion::Size size)
{
    static constexpr std::string_view names[]{
        "Small",
        "Medium",
        "Large",
    };

    return names[size];
}

std::string Potion::getName() const
{
    std::stringstream result{};
    result << Potion::getPotionSizeName(getSize()) << " potion of " << Potion::getPotionTypeName(getType());
    return result.str();
}

Potion Potion::getRandomPotion()
{
    return Potion{
        static_cast<Potion::Type>(Random::get(0, max_type - 1)),
        static_cast<Potion::Size>(Random::get(0, max_size - 1)),
    };
}

// Creature
Creature::Creature(std::string_view name, char symbol, int health, int damage, int gold)
    : m_name{name}, m_symbol{symbol}, m_health{health}, m_damage{damage}, m_gold{gold}
{
}

const std::string &Creature::getName() const { return m_name; }
char Creature::getSymbol() const { return m_symbol; }
int Creature::getHealth() const { return m_health; }
int Creature::getDamage() const { return m_damage; }
int Creature::getGold() const { return m_gold; }

void Creature::reduceHealth(int health) { m_health -= health; }
bool Creature::isDead() const { return m_health <= 0; }
void Creature::addGold(int gold) { m_gold += gold; }

// Monster
Monster::Monster(Monster::Type type) : Creature{monsterData[type]} {}

Monster Monster::getRandomMonster()
{
    int num{Random::get(0, max_types - 1)};
    return Monster{static_cast<Monster::Type>(num)};
}

// Player
Player::Player(std::string_view name) : Creature{name, '@', 10, 1, 0} {}
Player::~Player()
{
    std::cout << "Destruction player" << std::endl;
}

void Player::levelUp()
{
    ++this->m_level;
    ++this->m_damage;
}

void Player::drinkPotion(const Potion &potion)
{
    switch (potion.getType())
    {
    case Potion::health:
        m_health += (potion.getSize() == Potion::large) ? 5 : 2;
        break;
    case Potion::strength:
        ++m_damage;
        break;
    case Potion::poison:
        reduceHealth(1);
        break;
    case Potion::max_type:
        break;

    default:
        break;
    }
}

int Player::getLevel() const { return m_level; }
bool Player::hasWon() const { return m_level > 20; }

// Game
void Game::onMonsterKilled(Player &player, const Monster &monster)
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

void Game::attackMonster(Player &player, Monster &monster)
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

void Game::attackPlayer(Player &player, const Monster &monster)
{
    if (monster.isDead())
        return;

    player.reduceHealth(monster.getDamage());
    std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage. \n";
}

void Game::fightMonster(Player &player)
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

void Game::game()
{
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    Player player{playerName};
    std::cout << "Welcome to this game, " << player.getName() << ". \n";

    while (!player.isDead() && !player.hasWon())
        fightMonster(player);

    if (player.isDead())
    {
        std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold. \n";
        std::cout << "Too bad you can't take it with you! \n";
    }
    else
    {
        std::cout << "You wont the game with " << player.getGold() << " gold. \n";
    }
}