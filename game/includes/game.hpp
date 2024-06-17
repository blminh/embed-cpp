#ifndef __GAME_H__
#define __GAME_H__

#include "../../includes/Random.hpp"
#include "player.hpp"
#include "monster.hpp"

namespace Game
{
    void onMonsterKilled(Player &player, const Monster &monster);
    void attackMonster(Player &player, Monster &monster);
    void attackPlayer(Player &player, const Monster &monster);
    void fightMonster(Player &player);
};

#endif