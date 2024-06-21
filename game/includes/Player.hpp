#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include <string>
#include <string_view>
#include "Creature.hpp"
#include "Potion.hpp"

namespace Game
{
    class Player : public Creature
    {
    private:
        int mLevel_{1};

    public:
        Player(std::string_view name);
        ~Player();

        void levelUp();
        void drinkPotion(const Potion &potion);
        int getLevel() const;
        bool hasWon() const;
    };
};

#endif