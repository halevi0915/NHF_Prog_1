#include "game.h"

#include "logic.h"
#include "globals.h"
#include "visual.h"

Enemy generate_enemy(float diff, int stage) {

    Enemy forest_enemies[4] = {forest_enemy_1, forest_enemy_2, forest_enemy_3, forest_enemy_4};
    Enemy cave_enemies[4] = {cave_enemy_1, cave_enemy_2, cave_enemy_3, cave_enemy_4};
    Enemy castle_enemies[4] = {castle_enemy_1, castle_enemy_2, castle_enemy_3, castle_enemy_4};

    Enemy new_enemy;

    switch (stage%3) {
        case 0:
            new_enemy = forest_enemies[randint(0,3)];
            break;
        case 1:
            new_enemy = cave_enemies[randint(0,3)];
            break;
        case 2:
            new_enemy = castle_enemies[randint(0,3)];
            break;
    }
    return scale_enemy(reset_enemy(new_enemy), diff);
}

Enemy generate_boss(float diff, int stage) {
    
    Enemy bosses[3] = {forest_boss, castle_boss, castle_boss};
    return scale_enemy(reset_enemy(bosses[randint(0,2)]), diff);
}

// generate player, generate enemy --> generate game struct --> start game loop
Game init_new_game(float diff) {

    Game game = {
            .player = default_player,
            .enemy = generate_enemy(diff, 0),
            .turn = randint(0,1),
            .stage = 0,
            .diff = diff
    };
    return game;
}

void game_loop(Game g) {
    while (g.player.hp != 0) {
        if (g.turn) {                   // enemy turn
            
        } else {                        // player turn
            
        }
        g.turn = (g.turn) ? 0 : 1;
    }
}

char player_turn(Game g) {
    switch (game_action(g))
    {
    case 0:
        return 'a';
        break;
    
    default:
        return 'h';
        break;
    }
}

Game enemy_attack(Game g) {
    g.player.hp = max(g.player.hp - g.enemy.dmg, 0);
    return g;
}

Game enemy_heal(Game g) {
    g.enemy.hp = min(g.enemy.hp + enemy_heal_amount, g.enemy.max_hp);
    return g;
}

// resets the enemy hp and fire to the default
Enemy reset_enemy(Enemy e) {
    e.hp = e.max_hp;
    e.fire = 0;
    return e;
}

// scales the enemy hp, armor and exp reward by the difficulty level
Enemy scale_enemy(Enemy e, float diff) {
    e.max_hp *= diff;
    e.hp = e.max_hp;
    e.armor *= diff;
    e.exp_reward *= (1 / diff);
    return e;
}