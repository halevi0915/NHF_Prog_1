#include "debugmalloc.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "game.h"

#include "visual.h"
#include "logic.h"
#include "globals.h"

// linked list free
void free_inventory(Game* game_ptr) {
    Slot* iter = game_ptr->player.inventory;
    while (iter != NULL) {
        Slot* kov = iter->next;
        free(iter);
        iter = kov;
    }
}

// boosts current enemy stats by diff
void scale_enemy(Game* game_ptr) {
    game_ptr->enemy.max_hp *= game_ptr->diff;
    game_ptr->enemy.hp = game_ptr->enemy.max_hp;
    game_ptr->enemy.crit_ch = min(game_ptr->enemy.crit_ch * game_ptr->diff, 100);
    game_ptr->enemy.crit_dmg *= game_ptr->diff;
    game_ptr->enemy.exp_reward *= game_ptr->diff;
}

// enemy_per_stage enemy then boss: if boss -> +difficulty +new stage +enemy_index
// enemy_index is a counter for the current stage enemies
// chooses randomly from the appropriate stage
// scales the enemy as well
void generate_enemy(Game* game_ptr) {

    // FOREST ENEMIES -----------------------------------------------------------------------------------------------------
    static const Enemy forest_enemies[] = {
    {
        .name = "Slime",
        .dmg = 2,
        .max_hp = 10,
        .armor = 0,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 10,
    },
    {
        .name = "Wolf",
        .dmg = 7,
        .max_hp = 35,
        .armor = 5,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 15,
    },
    {
        .name = "Sapling",
        .dmg = 3,
        .max_hp = 50,
        .armor = 15,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 15,
    },
    {
        .name = "Forest Elf",
        .dmg = 10,
        .max_hp = 80,
        .armor = 5,
        .crit_ch = 10,
        .crit_dmg = 20,
        .exp_reward = 30,
    }
    };

    // CAVE ENEMIES -------------------------------------------------------------------------------------------------------
    static const Enemy cave_enemies[] = {
    {
        .name = "Zombie",
        .dmg = 8,
        .max_hp = 120,
        .armor = 8,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 40,
    },
    {
        .name = "Skeleton",
        .dmg = 12,
        .max_hp = 80,
        .armor = 10,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 40, 
    },
    {
        .name = "Spider",
        .dmg = 4,
        .max_hp = 60,
        .armor = 0,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 30,
    },
    {
        .name = "Goblin",
        .dmg = 3,
        .max_hp = 30,
        .armor = 10,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 20,
    }
    };

    // CASTLE ENEMIES -----------------------------------------------------------------------------------------------------
    static const Enemy castle_enemies[] = {
    {
        .name = "Cursed Knight",
        .dmg = 20,
        .max_hp = 200,
        .armor = 10,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 100,
    },
    {
        .name = "Necromancer",
        .dmg = 5,
        .max_hp = 50,
        .armor = 10,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 60,
    },
    {
        .name = "Cultist",
        .dmg = 15,
        .max_hp = 100,
        .armor = 10,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 80,
    },
    {
        .name = "Sorcerer",
        .dmg = 25,
        .max_hp = 70,
        .armor = 10,
        .crit_ch = 10,
        .crit_dmg = 15,
        .exp_reward = 120,
    }
    };

    // BOSSES -------------------------------------------------------------------------------------------------------------
    static const Enemy forest_boss = {
        .name = "Fire Dragon",
        .dmg = 15,
        .max_hp = 200,
        .armor = 30,
        .crit_ch = 25,
        .crit_dmg = 25,
        .exp_reward = 300,
    };

    static const Enemy cave_boss = {
        .name = "Stone Guardian",
        .dmg = 10,
        .max_hp = 1000,
        .armor = 20,
        .crit_ch = 1,
        .crit_dmg = 100,
        .exp_reward = 500,
    };

    static const Enemy castle_boss = {
        .name = "Evil Wizard",
        .dmg = 30,
        .max_hp = 500,
        .armor = 30,
        .crit_ch = 30,
        .crit_dmg = 50,
        .exp_reward = 1000,
    };

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

// difficulty -> diff menu
// preset default player
// generates an enemy and scales it
// puts the new game struct into the given ptr
void create_new_game(Game* game_ptr) {
    float diff = diff_menu();

    Player new_player = {
        .name = "Wizard",
        .lvl = 1,
        .exp = 0,
        .next_level_exp = exp_scale,
        .inventory = NULL,
        .item_count = 0,

        .exp_boost = 10,
        .heal_potion = 3,

        .max_hp = 100,
        .hp = 100,
        .heal_amount = 50,

        .max_mana = 200,
        .mana = 200,
        .rest_amount = 50,
        
        .armor = 10,
        .crit_ch = 10,
        .crit_dmg = 15,
        .miss_ch = 5,
        .dodge_ch = 10,

        .zap_cost = 10,
        .zap_dmg = 20,
        .zap_stun_ch = 10,

        .charge_cost = 20,
        .charge_up = 1,
        .current_charge = 0,

        .meteor_cost = 50,
        .meteor_dmg = 30,
        .meteor_fire = 1
    };

    Game new_game = {
        .player = new_player,
        .turn = randint(0,1),
        .stage = 0,
        .enemy_index = 0,
        .diff = diff
    };
    *game_ptr = new_game;
    generate_enemy(game_ptr);
    scale_enemy(game_ptr);
}

// random rng for rarity 
// chooses randomly from the appropriate rarity
// rarity chances are hardcoded
// item_good -> stats cant go past the limit: if stat is at the limit -> roll another item
// generate Item from ItemBase -> generate random stat beetwheen the min and max
Item genetrate_item(Game* game_ptr) {

    // ITEMS --------------------------------------------------------------------------------------------------------------

    static const ItemBase common_items[] = {
    {
        .name = "Heart Band",
        .stat_id = max_hp,
        .boost_min = 10,
        .boost_max = 30,
    },
    {
        .name = "Mana Ring",
        .stat_id = max_mana,
        .boost_min = 20,
        .boost_max = 60,
    },
    {
        .name = "Iron Guard",
        .stat_id = armor,
        .boost_min = 1,
        .boost_max = 5,
    },
    {
        .name = "Sharp Eye",
        .stat_id = crit_ch,
        .boost_min = 1,
        .boost_max = 5,
    },
    {
        .name = "Ruin Blade",
        .stat_id = crit_dmg,
        .boost_min = 1,
        .boost_max = 5,
    },
    {
        .name = "Thunder Wand",
        .stat_id = zap_dmg,
        .boost_min = 5,
        .boost_max = 15,
    },
    {
        .name = "Heal Flask",
        .stat_id = heal_potion,
        .boost_min = 1,
        .boost_max = 3,
    }
    };

    static const ItemBase rare_items[] = {
    {
        .name = "Wisdom Charm",
        .stat_id = exp_boost,
        .boost_min = 1,
        .boost_max = 5,
    },
    {
        .name = "Blur Veil",
        .stat_id = miss_ch,
        .boost_min = 1,
        .boost_max = 5,
    },
    {
        .name = "Spark Seal",
        .stat_id = zap_cost,
        .boost_min = 1,
        .boost_max = 5,
    },
    {
        .name = "Quick Rune",
        .stat_id = charge_cost,
        .boost_min = 1,
        .boost_max = 5,
    },
    {
        .name = "Regen Tonic",
        .stat_id = heal_amount,
        .boost_min = 15,
        .boost_max = 35,
    },
    {
        .name = "Peace Pendant",
        .stat_id = rest_amount,
        .boost_min = 25,
        .boost_max = 65,
    }
    };

    static const ItemBase epic_items[] = {
    {
        .name = "Swift Boots", 
        .stat_id = dodge_ch,
        .boost_min = 5,
        .boost_max = 15,
    },
    {
        .name = "Shock Rod",
        .stat_id = zap_stun_ch,
        .boost_min = 1,
        .boost_max = 5,
    },
    {
        .name = "Star Staff",
        .stat_id = meteor_cost,
        .boost_min = 5,
        .boost_max = 15,
    },
    {
        .name = "Fury Core",
        .stat_id = meteor_dmg,
        .boost_min = 5,
        .boost_max = 10,
    }
    };

    static const ItemBase legendary_items[] = {
    {
        .name = "Focus Gem",
        .stat_id = charge_up,
        .boost_min = 1,
        .boost_max = 3,
    },
    {
        .name = "Inferno Orb",
        .stat_id = meteor_fire,
        .boost_min = 1,
        .boost_max = 3,
    }
    };

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

// linked list: starting ptr is stored in the player struct
// slot is the linked list element
// generates new slot with the input item
// appends it to the end
// adds the itemstat to the player stat with a limit to the stat
// RETURNS A FORMATTED STR about the new item
char* add_item(Game* game_ptr, const Item item) {
    Slot* new_slot = (Slot*)malloc(sizeof(Slot));
    if (new_slot == NULL) {perror("slot alloc error"); exit(1);}
    new_slot->next = NULL;
    new_slot->contents = item;

    Slot* end_finder = game_ptr->player.inventory;
    if (end_finder == NULL) game_ptr->player.inventory = new_slot;
    else {
        while (end_finder->next != NULL) end_finder = end_finder->next;
        end_finder->next = new_slot;
    }
    game_ptr->player.item_count++;

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

// spell No.1 ZAP
// subtract mana cost
// increased dmg based on current_charge
// calculate dmg based on enemy.armor
// can miss -> miss_ch: mana and charge still gets taken away
// normal hit can stun -> stun_ch
// can crit -> crit_ch: increased dmg, guaranteed stun
// stun: if stunned makes the enemy skip a turn
// RETURNS A FORMATTED STR about the result
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

// spell No.2 OVERCHARGE
// subtract mana cost
// can miss -> miss_ch: mana still gets taken away
// can crit -> gives more charge
// charge is added to the player.current_charge: makes the next cast more powerful
// RETURNS A FORMATTED STR about the result
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

// spell No.3 METEOR SHOWER
// subtract mana cost
// increased dmg and fire_stacks based on current_charge
// calculate dmg based on enemy.armor
// can miss -> miss_ch: mana and charge still gets taken away
// applies fire stacks to the enemy: gets burn dmg each turn
// can crit -> crit_ch: increased dmg, more fire stacks
// RETURNS A FORMATTED STR about the result
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

// heals the player
// RETURNS A FORMATTED STR about the result
char* player_heal(Game* game_ptr) {
    game_ptr->player.hp = min(game_ptr->player.hp + game_ptr->player.heal_amount, game_ptr->player.max_hp);
    game_ptr->player.heal_potion -= 1;
    return format_string("You healed (+%d hp)", game_ptr->player.heal_amount);
}

// restores mana to the player
// RETURNS A FORMATTED STR about the result
char* player_rest(Game* game_ptr) {
    game_ptr->player.mana = min(game_ptr->player.mana + game_ptr->player.rest_amount, game_ptr->player.max_mana);
    return format_string("You rested (+%d mana)", game_ptr->player.rest_amount);
}


// two types of action: one end the turn and the second dosent: turn_running
// calls game_action menu: player can choose an action or pause
// if paused: wait for result and if quit/save was choosen: return with the value: game loop handes the quit/save
// other action: checks mana, heal_potion
// call the action function: display the result formatted str game_msg()
// update the turn_running
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

// enemy ai
// if stunned skip turn
// if enemy.hp is below enemy_heal_threshold: heal else attack
// heal: enemy_heal_amount scaled by diff
// attack: calculate dmg -> player.armor
// can miss -> player.dodge_ch
// can crit -> crit_ch: increased dmg
// display the result formatted str game_msg()
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

// there is no enemy that applies status (fire) to the player
// void player_status(Game* game_ptr) {
//
// }

// if enemy is on fire: apply the dmg and decrease the fire
void enemy_status(Game* game_ptr) {
    if (game_ptr->enemy.fire > 0) {
        game_ptr->enemy.hp = max(game_ptr->enemy.hp - fire_dmg, 0);
        game_ptr->enemy.fire -= 1;
        game_msg(format_string("%s is burning! (%d dmg)", game_ptr->enemy.name, fire_dmg), 1, game_ptr);
    }
}

// checks if the enemy is dead
// if yes: give xp scaled by diff
// check if next lvl is reached: generate 3 items and call game_item menu:
// player chooses 1 from the 3
// add the item to the inventory
// generate new enemny
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

// if player dead return 1: ends the game loop
int player_death(Game* game_ptr) {
    if (game_ptr->player.hp == 0) {game_over(game_ptr); return 0;}
    return 1;
}

// while the game is running
// cycle beetwheen turns 0: enemy 1: player
// player turn: call player_turn: quit/save if needed, check if enemy is dead after the player turn
// enemy turn: check status->check if dead, call enemy turn->check if player is dead
// if the loop ends free the linked list
void game_loop(Game* game_ptr) {
    int game_running = 1;
    while (game_running) {    
        if (game_ptr->turn) {
            //player_status(game_ptr);
            //game_running = player_death(game_ptr);
            switch (player_turn(game_ptr)) {
                case 0: game_ptr->turn = 0; break;
                case 1:
                    save_game(game_ptr, save_name);
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
    free_inventory(game_ptr);
}