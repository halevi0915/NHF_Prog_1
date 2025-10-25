#include "game.h"

#include "visual.h"
#include "logic.h"
#include "globals.h"

Enemy scale_enemy(Enemy* enemy_ptr, float diff) {
    enemy_ptr->max_hp *= diff;
    enemy_ptr->hp = enemy_ptr->max_hp;
    enemy_ptr->armor *= diff;
    enemy_ptr->exp_reward *= (1 / diff);
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

        .max_mana = 200,
        .mana = 200,
        
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

char* zap(Game* game_ptr) {
    int dmg = game_ptr->player.zap_dmg * (game_ptr->player.current_charge * charge_mult + 1) * (1 - (game_ptr->enemy.armor / 100));
    game_ptr->enemy.hp = max(game_ptr->enemy.hp - dmg, 0);
    game_ptr->player.mana -= game_ptr->player.zap_cost;
    return format_string("%s got zapped! (%d dmg)", game_ptr->enemy.name, dmg);
}

char* charge(Game* game_ptr) {
    game_ptr->player.current_charge += 1;
    game_ptr->player.mana -= game_ptr->player.charge_cost;
    return format_string("Overcharge successful! (%dx)", game_ptr->player.current_charge);
}

char* meteor(Game* game_ptr) {
    int dmg = game_ptr->player.meteor_dmg * (game_ptr->player.current_charge * charge_mult + 1) * (1 - (game_ptr->enemy.armor / 100));
    game_ptr->enemy.hp = max(game_ptr->enemy.hp - dmg, 0);
    game_ptr->player.mana -= game_ptr->player.meteor_cost;
    return format_string("%s got blasted by a meteor! (%d dmg)", game_ptr->enemy.name, dmg);
}

char* player_heal(Game* game_ptr) {
    game_ptr->player.hp = min(game_ptr->player.hp + heal_amount, game_ptr->player.max_hp);
    game_ptr->player.heal_potion -= 1;
    return format_string("You healed! (+%d hp)", heal_amount);
}

char* rest(Game* game_ptr) {
    game_ptr->player.mana = min(game_ptr->player.mana + rest_amount, game_ptr->player.max_mana);
    return format_string("You rested! (+%d mana)", rest_amount);
}

int player_turn(Game* game_ptr) {
    int turn_running = 1;
    int pause_result;
    while (turn_running) {
        switch (game_action(game_ptr)) {
            case 0: // zap
                if (game_ptr->player.mana >= game_ptr->player.zap_cost) {
                    game_msg(zap(game_ptr), 1, game_ptr);
                    turn_running = 0;
                } else game_msg("Not enough mana!", 0, game_ptr);
                break;
            case 1: // overcharge
                if (game_ptr->player.mana >= game_ptr->player.charge_cost) {
                    game_msg(charge(game_ptr), 1, game_ptr);
                    turn_running = 0;
                } else game_msg("Not enough mana!", 0, game_ptr);
                break;
            case 2: // meteor shower
                if (game_ptr->player.mana >= game_ptr->player.meteor_cost) {
                    game_msg(meteor(game_ptr), 1, game_ptr);
                    turn_running = 0;
                } else game_msg("Not enough mana!", 0, game_ptr);
                break;
            case 3: // heal
                if (game_ptr->player.hp < game_ptr->player.max_hp) {
                    if (game_ptr->player.heal_potion > 0) {
                        game_msg(player_heal(game_ptr), 1, game_ptr);
                        turn_running = 0;
                    } else game_msg("No health potions remaning!", 0, game_ptr);
                } else game_msg("Cant heal! (hp is full)", 0, game_ptr);
                break;
            case 4: // rest
                if (game_ptr->player.mana < game_ptr->player.max_mana) {
                    game_msg(rest(game_ptr), 1, game_ptr);
                    turn_running = 0;
                } else game_msg("Cant rest! (mana is full)", 0, game_ptr);
                break;
            case -1: // pause
                pause_result = pause_menu();
                if (pause_result) return pause_result; // 0 resume 1 save 2 quit
                break;
        };
    }
    return 0; 
}

void enemy_turn(Game* gmae_ptr) {
    
}

void player_status(Game* game_ptr) {

}

void enemy_status(Game* game_ptr) {
    
}

int enemy_death(Game* game_ptr) {

}

int player_death(Game* game_ptr) {
    
}

void game_loop(Game* game_ptr) {
    int game_running = 1;
    while (game_running) {    
        if (game_ptr->turn) {
            player_status(game_ptr);
            // check player death
            switch (player_turn(game_ptr)) {
                case 0:
                    game_ptr->turn = 0;
                case 1:
                    //save_game(game_ptr);
                    break;
                case 2:
                    game_running = 0;
                    break;
            };
            // check enemy death
        } else {
            enemy_status(game_ptr);
            // check enemy death
            enemy_turn(game_ptr);
            // check player death
            game_msg("enemy turn", 0, game_ptr);
            game_ptr->turn = 1;
        }
    }
}