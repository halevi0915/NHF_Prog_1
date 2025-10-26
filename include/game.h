#ifndef GAME_H
#define GAME_H

#include "globals.h"

Game create_new_game();
void game_loop(Game* game_ptr);

#endif