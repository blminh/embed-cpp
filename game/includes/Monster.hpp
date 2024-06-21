#ifndef __GAME_MONSTER_H__
#define __GAME_MONSTER_H__

#include "Creature.hpp"

namespace Game
{
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
        inline static Creature mMonsterData_[]{
            Creature{"dragon", 'd', 20, 4, 100},
            Creature{"orc", 'o', 4, 2, 25},
            Creature{"slime", 's', 1, 1, 10}};
        static_assert(std::size(mMonsterData_) == max_types);
    };
};

#endif