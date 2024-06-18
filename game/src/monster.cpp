#include "../../includes/Random.hpp"
#include "../includes/monster.hpp"

namespace Game
{
    Monster::Monster(Monster::Type type) : Creature{mMonsterData_[type]} {}

    Monster Monster::getRandomMonster()
    {
        int num{Random::get(0, max_types - 1)};
        return Monster{static_cast<Monster::Type>(num)};
    }
};
