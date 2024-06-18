#include "../includes/creature.hpp"

namespace Game
{
    Creature::Creature(std::string_view name, char symbol, int health, int damage, int gold)
        : mName_{name}, mSymbol_{symbol}, mHealth_{health}, mDamage_{damage}, mGold_{gold}
    {
    }

    const std::string &Creature::getName() const { return mName_; }
    char Creature::getSymbol() const { return mSymbol_; }
    int Creature::getHealth() const { return mHealth_; }
    int Creature::getDamage() const { return mDamage_; }
    int Creature::getGold() const { return mGold_; }

    void Creature::reduceHealth(int health) { mHealth_ -= health; }
    bool Creature::isDead() const { return mHealth_ <= 0; }
    void Creature::addGold(int gold) { mGold_ += gold; }
};
