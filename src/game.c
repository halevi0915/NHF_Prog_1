#include "debugmalloc.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "game.h"

#include "visual.h"
#include "logic.h"
#include "globals.h"

void scale_enemy(Game* game_ptr) {
    game_ptr->enemy.max_hp *= game_ptr->diff;
    game_ptr->enemy.hp = game_ptr->enemy.max_hp;
    game_ptr->enemy.armor *= game_ptr->diff;
    game_ptr->enemy.crit_ch = min(game_ptr->enemy.crit_ch * game_ptr->diff, 100);
    game_ptr->enemy.crit_dmg *= game_ptr->diff;
    game_ptr->enemy.exp_reward *= game_ptr->diff;
}

void generate_enemy(Game* game_ptr) {
    Enemy new_enemy;
    if (game_ptr->enemy_index == enemy_per_stage) {
        switch (game_ptr->stage % stage_count) {
            case 0: new_enemy = forest_boss; break;
            case 1: new_enemy = cave_boss; break;
            case 2: new_enemy = castle_boss; break;
        };
        game_ptr->enemy_index = 0;
        game_ptr->stage++;
        game_ptr->diff *= diff_scale;
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

    Inventory new_inventory = {
        .size = 0,
        .contents = NULL
    };

    Player new_player = {
        .name = "Wizard",
        .lvl = 1,
        .exp = 0,
        .next_level_exp = exp_scale,
        .exp_boost = 10,
        .heal_potion = 3,
        .inventory = new_inventory,

        .max_hp = 100,
        .hp = 100,
        .heal_amount = 30,

        .max_mana = 200,
        .mana = 200,
        .rest_amount = 30,
        
        .armor = 10,
        .crit_ch = 10,
        .crit_dmg = 12,
        .miss_ch = 5,
        .dodge_ch = 10,

        .zap_cost = 20,
        .zap_dmg = 10,
        .zap_stun_ch = 10,

        .charge_cost = 40,
        .charge_up = 1,
        .current_charge = 0,

        .meteor_cost = 100,
        .meteor_dmg = 50,
        .meteor_fire = 1
    };

    Game new_game = {
        .player = new_player,
        .enemy = forest_enemies[0],
        .turn = randint(0,1),
        .stage = 0,
        .enemy_index = 0,
        .diff = diff
    };
    scale_enemy(&new_game);
    return new_game;
}

Item genetrate_item(Game* game_ptr) {
    int rng;
    ItemBase new_item_base;
    bool item_good;

    do {
        item_good = true;
        rng = randint(1, 100);
        if (rng <= 45) new_item_base = common_items[randint(0,6)];
        else if (rng > 45 && rng <= 75) new_item_base = rare_items[randint(0,5)];
        else if (rng > 75 && rng <= 95) new_item_base = epic_items[randint(0,3)];
        else new_item_base = legendary_items[randint(0,1)];

        if (new_item_base.stat_id == armor && game_ptr->player.armor == armor_cap) item_good = false;
        else if (new_item_base.stat_id == crit_ch && game_ptr->player.crit_ch == 100) item_good = false;
        else if (new_item_base.stat_id == miss_ch && game_ptr->player.miss_ch == 0) item_good = false;
        else if (new_item_base.stat_id == dodge_ch && game_ptr->player.dodge_ch == dodge_cap) item_good = false;
        else if (new_item_base.stat_id == zap_cost && game_ptr->player.zap_cost == 0) item_good = false;
        else if (new_item_base.stat_id == zap_stun_ch && game_ptr->player.zap_stun_ch == 100) item_good = false;
        else if (new_item_base.stat_id == charge_cost && game_ptr->player.charge_cost == 0) item_good = false;
        else if (new_item_base.stat_id == meteor_cost && game_ptr->player.meteor_cost == 0) item_good = false;

    } while (!item_good);
    Item new_item = {
        .stat_id = new_item_base.stat_id,
        .boost = randint(new_item_base.boost_min * 10, new_item_base.boost_max * 10) / 10.0
    };
    strcpy(new_item.name, new_item_base.name);
    return new_item;
}

char* add_item(Game* game_ptr, const Item item) {
    game_ptr->player.inventory.size++;
    game_ptr->player.inventory.contents = realloc(game_ptr->player.inventory.contents, game_ptr->player.inventory.size * sizeof(Item));
    if (game_ptr->player.inventory.contents == NULL) {printf("inv realloc error"); exit(1);}
    game_ptr->player.inventory.contents[game_ptr->player.inventory.size-1] = item;

    switch (item.stat_id) {
        case exp_boost: game_ptr->player.exp_boost += item.boost; break;
        case heal_potion: game_ptr->player.heal_potion += item.boost; break;
        case max_hp: game_ptr->player.max_hp += item.boost; break;
        case heal_amount: game_ptr->player.heal_amount += item.boost; break;
        case max_mana: game_ptr->player.max_mana += item.boost; break;
        case rest_amount: game_ptr->player.rest_amount += item.boost; break;
        case armor: game_ptr->player.armor = min(game_ptr->player.armor + item.boost, armor_cap); break;
        case crit_ch: game_ptr->player.crit_ch = min(game_ptr->player.crit_ch + item.boost, 100); break;
        case crit_dmg: game_ptr->player.crit_dmg += item.boost; break;
        case miss_ch: game_ptr->player.miss_ch = max(game_ptr->player.miss_ch - item.boost, 0); break;
        case dodge_ch: game_ptr->player.dodge_ch = min(game_ptr->player.dodge_ch + item.boost, dodge_cap); break;
        case zap_cost: game_ptr->player.zap_cost = max(game_ptr->player.zap_cost - item.boost, 0); break;
        case zap_dmg: game_ptr->player.zap_dmg += item.boost; break;
        case zap_stun_ch: game_ptr->player.zap_stun_ch = min(game_ptr->player.zap_stun_ch + item.boost, 100); break;
        case charge_cost: game_ptr->player.charge_cost = max(game_ptr->player.charge_cost - item.boost, 0); break;
        case charge_up: game_ptr->player.charge_up += item.boost; break;
        case meteor_cost: game_ptr->player.meteor_cost = max(game_ptr->player.meteor_cost - item.boost, 0); break;
        case meteor_dmg: game_ptr->player.meteor_dmg += item.boost; break;
        case meteor_fire: game_ptr->player.meteor_fire += item.boost; break;
    }
    return format_string("New item: %s!", item.name, item.boost);
}

char* zap(Game* game_ptr) {
    game_ptr->player.mana -= game_ptr->player.zap_cost;
    int dmg = game_ptr->player.zap_dmg * max(game_ptr->player.current_charge * charge_mult, 1) * (1 - (game_ptr->enemy.armor / 100.0));
    if (game_ptr->player.current_charge > 0) game_ptr->player.current_charge = 0;

    if (calc_chance(game_ptr->player.miss_ch)) return format_string("Zap misses! (%d%%)", game_ptr->player.miss_ch);
    else if (calc_chance(game_ptr->player.crit_ch)) {
        dmg *= (game_ptr->player.crit_dmg / 10.0);
        game_ptr->enemy.stun = 1;
        game_ptr->enemy.hp = max(game_ptr->enemy.hp - dmg, 0);
        return format_string("Critical Zap hit! (%d dmg - stun)", dmg);
    }
    game_ptr->enemy.hp = max(game_ptr->enemy.hp - dmg, 0);
    if (calc_chance(game_ptr->player.zap_stun_ch)) {
        game_ptr->enemy.stun = 1;
        return format_string("Zap stuns! (%d dmg - stun)", dmg);
    }
    return format_string("Zap hits! (%d dmg)", dmg);
}

char* charge(Game* game_ptr) {
    game_ptr->player.mana -= game_ptr->player.charge_cost;
    if (calc_chance(game_ptr->player.miss_ch)) return format_string("Charge failed! (%d%%)", game_ptr->player.miss_ch);
    if (calc_chance(game_ptr->player.crit_ch)) {
        game_ptr->player.current_charge += game_ptr->player.charge_up * (int)(game_ptr->player.crit_dmg / 10.0);
        return format_string("Perfect charge! (+%dx)", game_ptr->player.charge_up * (int)(game_ptr->player.crit_dmg / 10.0));
    }
    game_ptr->player.current_charge += game_ptr->player.charge_up;
    return format_string("Charge successful! (+%dx)", game_ptr->player.charge_up);
}

char* meteor(Game* game_ptr) {
    game_ptr->player.mana -= game_ptr->player.meteor_cost;
    int dmg = game_ptr->player.meteor_dmg * max(game_ptr->player.current_charge * charge_mult, 1) * (1 - (game_ptr->enemy.armor / 100.0));
    int fire = game_ptr->player.meteor_fire * max(game_ptr->player.current_charge * charge_mult, 1);
    if (game_ptr->player.current_charge > 0) game_ptr->player.current_charge = 0;

    if (calc_chance(game_ptr->player.miss_ch)) return format_string("Meteor misses! (%d%%)", game_ptr->player.miss_ch);
    else if (calc_chance(game_ptr->player.crit_ch)) {
        dmg *= (game_ptr->player.crit_dmg / 10.0);
        fire *= (int)(game_ptr->player.crit_dmg / 10.0);
        game_ptr->enemy.hp = max(game_ptr->enemy.hp - dmg, 0);
        game_ptr->enemy.fire += fire;
        return format_string("Critical Meteor hit! (%d dmg - %d fire)", dmg, fire);
    }
    game_ptr->enemy.hp = max(game_ptr->enemy.hp - dmg, 0);
    game_ptr->enemy.fire += fire;
    return format_string("Meteor hits! (%d dmg - %d fire)", dmg, fire);
}

char* player_heal(Game* game_ptr) {
    game_ptr->player.hp = min(game_ptr->player.hp + game_ptr->player.heal_amount, game_ptr->player.max_hp);
    game_ptr->player.heal_potion -= 1;
    return format_string("You healed (+%d hp)", game_ptr->player.heal_amount);
}

char* player_rest(Game* game_ptr) {
    game_ptr->player.mana = min(game_ptr->player.mana + game_ptr->player.rest_amount, game_ptr->player.max_mana);
    return format_string("You rested (+%d mana)", game_ptr->player.rest_amount);
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
    if (game_ptr->enemy.stun == 1) {
        game_ptr->enemy.stun = 0;
        game_msg(format_string("%s is stunned!", game_ptr->enemy.name), 1, game_ptr);
    }
    else if (game_ptr->enemy.hp <= game_ptr->enemy.max_hp * (enemy_heal_threshold / 100.0)) {
        game_ptr->enemy.hp = min(game_ptr->enemy.hp + enemy_heal_amount * game_ptr->diff, game_ptr->enemy.max_hp);
        game_msg(format_string("%s healed! (+%d hp)", game_ptr->enemy.name, enemy_heal_amount), 1, game_ptr);
    } else {
        if (calc_chance(game_ptr->player.dodge_ch)) game_msg(format_string("%s missed you! (%d%%)", game_ptr->enemy.name, game_ptr->player.dodge_ch), 1, game_ptr);
        else {
            int dmg = game_ptr->enemy.dmg * (1 - (game_ptr->player.armor / 100.0));
            if (calc_chance(game_ptr->enemy.crit_ch)) {
                dmg *= (game_ptr->enemy.crit_dmg / 10.0);
                game_msg(format_string("%s landed a critical hit! (%d dmg)", game_ptr->enemy.name, dmg), 1, game_ptr);
            } else game_msg(format_string("%s hit you! (%d dmg)", game_ptr->enemy.name, dmg), 1, game_ptr);
            game_ptr->player.hp = max(game_ptr->player.hp - dmg, 0);
        }
    }
}

// void player_status(Game* game_ptr) {
//     // no need for now
// }

void enemy_status(Game* game_ptr) {
    if (game_ptr->enemy.fire > 0) {
        game_ptr->enemy.hp = max(game_ptr->enemy.hp - fire_dmg, 0);
        game_ptr->enemy.fire -= 1;
        game_msg(format_string("%s is burning! (%d dmg)", game_ptr->enemy.name, fire_dmg), 1, game_ptr);
    }
}

void enemy_death(Game* game_ptr) {
    if (game_ptr->enemy.hp == 0) {
        const int exp = game_ptr->enemy.exp_reward * (game_ptr->player.exp_boost / 10.0);
        game_ptr->player.exp += exp;
        game_msg(format_string("%s has been defeated! (%d exp)", game_ptr->enemy.name, exp), 1, game_ptr);

        while (game_ptr->player.exp >= game_ptr->player.next_level_exp) {
            game_ptr->player.exp -= game_ptr->player.next_level_exp;
            game_ptr->player.lvl += 1;
            game_ptr->player.next_level_exp = game_ptr->player.lvl * exp_scale;
            game_msg("Level up!", 0, game_ptr);

            Item new_item;
            Item items[3] = {genetrate_item(game_ptr)};
            do { new_item = genetrate_item(game_ptr);
            } while (new_item.stat_id == items[0].stat_id);
            items[1] = new_item;
            do { new_item = genetrate_item(game_ptr);
            } while (new_item.stat_id == items[0].stat_id || new_item.stat_id == items[1].stat_id);
            items[2] = new_item;

            switch (game_item(items, game_ptr)) {
                case 0: game_msg(add_item(game_ptr, items[0]), 1, game_ptr); break;
                case 1: game_msg(add_item(game_ptr, items[1]), 1, game_ptr); break;
                case 2: game_msg(add_item(game_ptr, items[2]), 1, game_ptr); break;
            }
        }

        generate_enemy(game_ptr);
        game_msg(format_string("New enemy approaches! (%s)", game_ptr->enemy.name), 1, game_ptr);
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
            //player_status(game_ptr);
            //game_running = player_death(game_ptr);
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
    free(game_ptr->player.inventory.contents);
}