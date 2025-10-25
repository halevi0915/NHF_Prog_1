#ifndef GAME_H
#define GAME_H

#include "globals.h"

Game create_new_game(float diff);
void game_loop(Game* game_ptr);

#endif