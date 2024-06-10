#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <array>
#include "Random.h"

class Potion
{
public:
    enum Type
    {
        health,
        strength,
        poison,
        max_type
    };

    enum Size
    {
        small,
        medium,
        large,
        max_size
    };

    Potion(Type type, Size size) : m_type{type}, m_size{size} {}

    Type getType() const
    {
        return m_type;
    }

    Size getSize() const
    {
        return m_size;
    }

    static std::string_view getPotionTypeName(Type type)
    {
        static constexpr std::string_view names[]{
            "Health",
            "Strength",
            "Poison",
        };
        return names[type];
    }

    static std::string_view getPotionSizeName(Size size)
    {
        static constexpr std::string_view names[]{
            "Small",
            "Medium",
            "Large",
        };

        return names[size];
    }

    std::string getName() const
    {
        std::stringstream result{};
        result << getPotionSizeName(getSize()) << " potion of " << getPotionTypeName(getType());
        return result.str();
    }

    static Potion getRandomPotion()
    {
        return Potion{
            static_cast<Type>(Random::get(0, max_type - 1)),
            static_cast<Size>(Random::get(0, max_size - 1)),
        };
    }

private:
    Type m_type{};
    Size m_size{};
};

class Creature
{
protected:
    std::string m_name;
    char m_symbol{};
    int m_health{};
    int m_damage{};
    int m_gold{};

public:
    Creature(std::string_view name, char symbol, int health, int damage, int gold)
        : m_name{name}, m_symbol{symbol}, m_health{health}, m_damage{damage}, m_gold{gold}
    {
    }

    const std::string &getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    int getHealth() const { return m_health; }
    int getDamage() const { return m_damage; }
    int getGold() const { return m_gold; }

    void reduceHealth(int health) { m_health -= health; }
    bool isDead() const { return m_health <= 0; }
    void addGold(int gold) { m_gold += gold; }
};

class Monster : public Creature
{
public:
    enum Type
    {
        dragon,
        orc,
        slime,
        max_types
    };

    Monster(Type type) : Creature{monsterData[type]} {}

    static Monster getRandomMonster()
    {
        int num{Random::get(0, max_types - 1)};
        return Monster{static_cast<Type>(num)};
    }

private:
    inline static Creature monsterData[]{
        Creature{"dragon", 'd', 20, 4, 100},
        Creature{"orc", 'o', 4, 2, 25},
        Creature{"slime", 's', 1, 1, 10}};
    static_assert(std::size(monsterData) == max_types);
};

class Player : public Creature
{
private:
    int m_level{1};

public:
    Player(std::string_view name) : Creature{name, '@', 10, 1, 0} {}
    ~Player()
    {
        std::cout << "Destruction player" << std::endl;
    }

    void levelUp()
    {
        ++this->m_level;
        ++this->m_damage;
    }

    void drinkPotion(const Potion &potion)
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

    int getLevel() const { return m_level; }
    bool hasWon() const { return m_level > 20; }
};

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
        // Generate a random potion
        auto potion{Potion::getRandomPotion()};

        std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
        char choice{};
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            // Apply the effect
            player.drinkPotion(potion);
            // Reveal the potion type and size
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

int main()
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

    return 0;
}