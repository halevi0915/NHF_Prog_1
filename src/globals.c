#include "globals.h"
#include "player.h"
#include "enemy.h"

// globals
int heal_amount = 40;

// difficulty multipilers - enemy stats
float easy_mult = 0.8;
float normal_mult = 1;
float hard_mult = 1.6;

Player default_player = {
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

    .meteor_cost = 100,
    .meteor_dmg = 50,
    .meteor_fire = 1,

    .heal_potion = 3,
};

// NORMAL ENEMIES -------------------------------------------------------------------------------------------------

// beginner enemies - FOREST
Enemy forest_enemy_1 = {
    .name = "Slime",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy forest_enemy_2 = {
    .name = "Wolf",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy forest_enemy_3 = {
    .name = "Sapling",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy forest_enemy_4 = {
    .name = "Forest Elf",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// mid-game enemies - CAVE
Enemy cave_enemy_1 = {
    .name = "Zombie",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy cave_enemy_2 = {
    .name = "Skeleton",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0 
};

Enemy cave_enemy_3 = {
    .name = "Spider",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy cave_enemy_4 = {
    .name = "Goblin",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// end-game enemies -  CASTLE

Enemy castle_enemy_1 = {
    .name = "Cursed Knight",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy castle_enemy_2 = {
    .name = "Necromancer",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy castle_enemy_3 = {
    .name = "Cultist",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy castle_enemy_4 = {
    .name = "Sorcerer",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// BOSSES ---------------------------------------------------------------------------------------------------------

// FOREST boss
Enemy forest_boss = {
    .name = "Fire Dragon",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// CAVE boss
Enemy cave_boss = {
    .name = "Stone Guardian",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// DEMONIC CASTLE boss
Enemy castle_boss = {
    .name = "Evil Wizard",
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};