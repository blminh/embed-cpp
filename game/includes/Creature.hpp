#ifndef __GAME_CREATURE_H__
#define __GAME_CREATURE_H__

#include <string>
#include <string_view>

namespace Game
{
    class Creature
    {
    protected:
        std::string mName_;
        char mSymbol_{};
        int mHealth_{};
        int mDamage_{};
        int mGold_{};

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
};

#endif