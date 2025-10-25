#ifndef GAME_H
#define GAME_H

#include "logic.h"
#include "globals.h"
#include "visual.h"

Enemy scale_enemy(Enemy* e, float diff);
Enemy generate_enemy(float diff, int stage);
Enemy generate_boss(float diff, int stage);
Game create_new_game(float diff);

#endif