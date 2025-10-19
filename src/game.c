#include "game.h"
#include "player.h"
#include "enemy.h"
#include "menus.h"
#include "logic.h"
#include "globals.h"

typedef struct g {        // default value
    Player player;
    Enemy enemy;
    int turn;           // player: 0 enemy: 1 default: 0
    int stage;          // forest: 0 cave: 1 castle: 2 default: 0
    int diff;           // easy: 0.8 normal: 1 hard: 1.6 (enemy stat multiplier)

} Game;

Enemy generate_enemy(float diff, int stage) {

    Enemy forest_enemies[4] = {forest_enemy_1, forest_enemy_2, forest_enemy_3, forest_enemy_4};
    Enemy cave_enemies[4] = {cave_enemy_1, cave_enemy_2, cave_enemy_3, cave_enemy_4};
    Enemy castle_enemies[4] = {castle_enemy_1, castle_enemy_2, castle_enemy_3, castle_enemy_4};

    switch (stage%3) {
        case 0:
            return scale_enemy(reset_enemy(forest_enemies[random_element(4)]), diff);
            break;
        case 1:
            return scale_enemy(reset_enemy(cave_enemies[random_element(4)]), diff);
            break;
        case 2:
            return scale_enemy(reset_enemy(castle_enemies[random_element(4)]), diff);
            break;
    }
}

Enemy generate_boss(float diff, int stage) {
    
    Enemy bosses[3] = {forest_boss, castle_boss, castle_boss};
    return scale_enemy(reset_enemy(bosses[random_element(3)]), diff);
}

// generate player, generate enemy --> generate game struct --> start game loop
Game start_new_game() {
    int diff_result = diff_menu();
    float diff;
    switch (diff_result) {
        case 0:             // easy
            diff = 0.8;
            break;
        case 1:             // normal
            diff = 1;
            break;
        case 2:             // hard
            diff = 1.6;
            break;
    }

    Game game = {
            .player = default_player,
            .enemy = generate_enemy(diff, 0),
            .turn = 0,
            .stage = 0,
            .diff = diff
    };
    return game;
}