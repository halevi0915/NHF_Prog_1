#include "game.h"

#include "logic.h"
#include "globals.h"
#include "visual.h"

// scales the enemy hp, armor and exp reward by the difficulty level
Enemy scale_enemy(Enemy* e, float diff) {
    e->max_hp *= diff;
    e->hp = e->max_hp;
    e->armor *= diff;
    e->exp_reward *= (1 / diff);
}

Enemy generate_enemy(float diff, int stage) {
    Enemy new_enemy;
    switch (stage) {
        case 0: new_enemy = forest_enemies[randint(0,3)];
        case 1: new_enemy = cave_enemies[randint(0,3)];
        case 2: new_enemy = castle_enemies[randint(0,3)];
    };
    scale_enemy(&new_enemy, diff);
    return new_enemy; 
}

Enemy generate_boss(float diff, int stage) {
    Enemy new_boss;
    switch (stage) {
        case 0: new_boss = forest_boss;
        case 1: new_boss = cave_boss;
        case 2: new_boss = castle_boss;
    };
    scale_enemy(&new_boss, diff);
    return new_boss;
}

Game create_new_game(float diff) {
    Player new_player = {
        .lvl = 1,
        .exp = 0,
        .next_level_exp = 10,

        .max_hp = 100,
        .hp = 100,
        .hp_regen = 0,

        .max_mana = 200,
        .mana = 200,
        .mana_regen = 0,
        
        .armor = 0,

        .zap_cost = 20,
        .zap_dmg = 10,

        .charge_cost = 40,
        .charge_up = 1,
        .current_charge = 0,

        .meteor_cost = 100,
        .meteor_dmg = 50,
        .meteor_fire = 1,

        .heal_potion = 3,
    };

    Game new_game = {
        .player = new_player,
        .enemy = generate_enemy(diff, 0),
        .turn = randint(0,1),
        .stage = 0,
        .diff = diff,
    };
    return new_game;
}

// void game_loop(Game g) {
//     while (g.player.hp != 0) {
//         if (g.turn) {                   // enemy turn
            
//         } else {                        // player turn
            
//         }
//         g.turn = (g.turn) ? 0 : 1;
//     }
// }

// char player_turn(Game g) {
//     switch (game_action(g))
//     {
//     case 0:
//         return 'a';
//         break;
    
//     default:
//         return 'h';
//         break;
//     }
// }

// Game enemy_attack(Game g) {
//     g.player.hp = max(g.player.hp - g.enemy.dmg, 0);
//     return g;
// }

// Game enemy_heal(Game g) {
//     g.enemy.hp = min(g.enemy.hp + enemy_heal_amount, g.enemy.max_hp);
//     return g;
// }

