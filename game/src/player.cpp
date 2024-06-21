#include <iostream>
#include "../includes/Potion.hpp"
#include "../includes/Creature.hpp"
#include "../includes/Player.hpp"

namespace Game
{
    Player::Player(std::string_view name) : Creature{name, '@', 10, 1, 0} {}
    Player::~Player()
    {
        std::cout << "Destruction player" << std::endl;
    }

    void Player::levelUp()
    {
        ++this->mLevel_;
        ++this->mDamage_;
    }

    void Player::drinkPotion(const Potion &potion)
    {
        switch (potion.getType())
        {
        case Potion::health:
            mHealth_ += (potion.getSize() == Potion::large) ? 5 : 2;
            break;
        case Potion::strength:
            ++mDamage_;
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

    int Player::getLevel() const { return mLevel_; }
    bool Player::hasWon() const { return mLevel_ > 20; }
};
