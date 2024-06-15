#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include "Random.hpp"
#include <string>
#include <string_view>

namespace Game
{
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
        Potion();
        Potion(Type type, Size size);
        ~Potion();

        Type getType() const;
        Size getSize() const;
        static std::string_view getPotionTypeName(Type type);
        static std::string_view getPotionSizeName(Size size);
        std::string getName() const;
        static Potion getRandomPotion();

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
        Creature(std::string_view name, char symbol, int health, int damage, int gold);
        const std::string &getName() const;
        char getSymbol() const;
        int getHealth() const;
        int getDamage() const;
        int getGold() const;
        void reduceHealth(int health);
        bool isDead() const;
        void addGold(int gold);
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

        Monster(Type type);

        static Monster getRandomMonster();

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
        Player(std::string_view name);
        ~Player();

        void levelUp();
        void drinkPotion(const Potion &potion);
        int getLevel() const;
        bool hasWon() const;
    };

    void onMonsterKilled(Player &player, const Monster &monster);
    void attackMonster(Player &player, Monster &monster);
    void attackPlayer(Player &player, const Monster &monster);
    void fightMonster(Player &player);
    void game();
};

#endif