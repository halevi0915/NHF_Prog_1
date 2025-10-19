#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "enemy.h"

typedef struct g {
    Player player;
    Enemy enemy;
    int turn;
    int stage;
    int diff;
} Game;

Game start_new_game();

#endif