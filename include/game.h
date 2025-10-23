#ifndef GAME_H
#define GAME_H

#include "logic.h"
#include "globals.h"
#include "visual.h"

Game init_new_game(float diff);
void game_loop(Game g);

char player_turn(Game g);

Game enemy_attack(Game g);
Game enemy_heal(Game g);

Enemy reset_enemy(Enemy e);
Enemy scale_enemy(Enemy e, float diff);

#endif