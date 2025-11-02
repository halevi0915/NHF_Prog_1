#include "game.h"

#include "visual.h"
#include "logic.h"
#include "globals.h"

Enemy scale_enemy(Game* game_ptr) {
    // stage alapjan is
    game_ptr->enemy.max_hp *= game_ptr->diff;
    game_ptr->enemy.hp = game_ptr->enemy.max_hp;
    game_ptr->enemy.armor *= game_ptr->diff;
    game_ptr->enemy.exp_reward *= (1 / game_ptr->diff);
}

Enemy generate_enemy(Game* game_ptr) {
    Enemy new_enemy;
    if (game_ptr->enemy_index == enemy_per_stage) {
        switch (game_ptr->stage % stage_count) {
            case 0: new_enemy = forest_boss; break;
            case 1: new_enemy = cave_boss; break;
            case 2: new_enemy = castle_boss; break;
        };
        game_ptr->enemy_index = 0;
        game_ptr->stage++;
    } else {
        switch (game_ptr->stage % stage_count) {
            case 0: new_enemy = forest_enemies[randint(0,3)]; break;
            case 1: new_enemy = cave_enemies[randint(0,3)]; break;
            case 2: new_enemy = castle_enemies[randint(0,3)]; break;
        };
        game_ptr->enemy_index++;
    }
    game_ptr->enemy = new_enemy;
    scale_enemy(game_ptr);
}

Game create_new_game() {
    float diff = diff_menu();
    Player new_player = {
        .lvl = 1,
        .exp = 0,
        .next_level_exp = 1 * exp_scale,

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
        .enemy = forest_enemies[0],
        .turn = randint(0,1),
        .stage = 0,
        .enemy_index = 0,
        .diff = diff,
    };
    scale_enemy(&new_game);
    return new_game;
}

char* zap(Game* game_ptr) {
    int dmg = game_ptr->player.zap_dmg * max(game_ptr->player.current_charge * charge_mult, 1) * (1 - (game_ptr->enemy.armor / 100));
    game_ptr->enemy.hp = max(game_ptr->enemy.hp - dmg, 0);
    game_ptr->player.mana -= game_ptr->player.zap_cost;
    if (game_ptr->player.current_charge > 0) game_ptr->player.current_charge = 0;
    return format_string(zap_msg[randint(0, 17)], dmg);
}

char* charge(Game* game_ptr) {
    game_ptr->player.current_charge += 1;
    game_ptr->player.mana -= game_ptr->player.charge_cost;
    return format_string(charge_msg[randint(0, 19)], game_ptr->player.current_charge);
}

char* meteor(Game* game_ptr) {
    int dmg = game_ptr->player.meteor_dmg * max(game_ptr->player.current_charge * charge_mult, 1) * (1 - (game_ptr->enemy.armor / 100));
    game_ptr->enemy.hp = max(game_ptr->enemy.hp - dmg, 0);
    game_ptr->player.mana -= game_ptr->player.meteor_cost;
    game_ptr->enemy.fire += game_ptr->player.meteor_fire;
    if (game_ptr->player.current_charge > 0) game_ptr->player.current_charge = 0;
    return format_string(meteor_msg[randint(0, 15)], dmg);
}

char* player_heal(Game* game_ptr) {
    game_ptr->player.hp = min(game_ptr->player.hp + heal_amount, game_ptr->player.max_hp);
    game_ptr->player.heal_potion -= 1;
    return format_string(heal_msg[randint(0, 19)], heal_amount);
}

char* player_rest(Game* game_ptr) {
    game_ptr->player.mana = min(game_ptr->player.mana + rest_amount, game_ptr->player.max_mana);
    return format_string(rest_msg[randint(0, 18)], rest_amount);
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
                    game_msg(player_rest(game_ptr), 1, game_ptr);
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

void enemy_turn (Game* game_ptr) {
    if (game_ptr->enemy.hp <= game_ptr->enemy.max_hp * enemy_heal_threshold) {
        game_ptr->enemy.hp = min(game_ptr->enemy.hp + enemy_heal_amount, game_ptr->enemy.max_hp);
        game_msg(format_string("%s healed! (+%d hp)", game_ptr->enemy.name, enemy_heal_amount), 1, game_ptr);
    } else {
        int dmg = game_ptr->enemy.dmg * (1 - (game_ptr->player.armor / 100));
        game_ptr->player.hp = max(game_ptr->player.hp - dmg, 0);
        game_msg(format_string("%s attacked you! (%d dmg)", game_ptr->enemy.name, dmg), 1, game_ptr);
    }
}

void player_status(Game* game_ptr) {
    // wip
    // no need now
}

void enemy_status(Game* game_ptr) {
    if (game_ptr->enemy.fire > 0) {
        game_ptr->enemy.hp = max(game_ptr->enemy.hp - fire_dmg, 0);
        game_ptr->enemy.fire -= 1;
        game_msg(format_string("%s is burning! (%d dmg)", game_ptr->enemy.name, fire_dmg), 1, game_ptr);
    }
}

int enemy_death(Game* game_ptr) {
    if (game_ptr->enemy.hp == 0) {
        game_ptr->player.exp += game_ptr->enemy.exp_reward;
        game_msg(format_string("%s has been defeated! (%d exp)", game_ptr->enemy.name, game_ptr->enemy.exp_reward), 1, game_ptr);

        generate_enemy(game_ptr);
        game_msg(format_string("New enemy approaches! (%s)", game_ptr->enemy.name), 1, game_ptr);

        if (game_ptr->player.exp >= game_ptr->player.next_level_exp) {
            game_ptr->player.exp -= game_ptr->player.next_level_exp;
            game_ptr->player.lvl += 1;
            game_ptr->player.next_level_exp = game_ptr->player.lvl * exp_scale;
            game_msg("Level up!", 0, game_ptr);
            // item choose
        }
    }
}

int player_death(Game* game_ptr) {
    if (game_ptr->player.hp == 0) {game_over(game_ptr); return 0;}
    return 1;
}

void game_loop(Game* game_ptr) {
    int game_running = 1;
    while (game_running) {    
        if (game_ptr->turn) {
            player_status(game_ptr);
            game_running = player_death(game_ptr);
            switch (player_turn(game_ptr)) {
                case 0: game_ptr->turn = 0; break;
                case 1:
                    //save_game(game_ptr);
                    break;
                case 2: game_running = 0; break;
            };
            enemy_death(game_ptr);
        } else {
            enemy_status(game_ptr);
            enemy_death(game_ptr);
            enemy_turn(game_ptr);
            game_running = player_death(game_ptr);
            game_ptr->turn = 1;
        }
    }
}