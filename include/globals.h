#ifndef GLOBALS_H
#define GLOBALS_H

#include "player.h"
#include "enemy.h"

extern Player default_player;

extern int heal_amount;

extern float easy_mult;
extern float normal_mult;
extern float hard_mult;

extern Enemy forest_enemy_1;
extern Enemy forest_enemy_2;
extern Enemy forest_enemy_3;
extern Enemy forest_enemy_4;

extern Enemy cave_enemy_1;
extern Enemy cave_enemy_2;
extern Enemy cave_enemy_3;
extern Enemy cave_enemy_4;

extern Enemy castle_enemy_1;
extern Enemy castle_enemy_2;
extern Enemy castle_enemy_3;
extern Enemy castle_enemy_4;

extern Enemy forest_boss;
extern Enemy cave_boss;
extern Enemy castle_boss;

#endif