#include "globals.h"

// GLOBALS ------------------------------------------------------------------------------------------------------------
const int heal_amount = 40;
const int enemy_heal_amount = 10;
const int rest_amount = 50;
const int fire_dmg = 10;
const int charge_mult = 2;

const float easy_diff_mult = 0.8;
const float normal_diff_mult = 1;
const float hard_diff_mult = 1.6;

int malloc_counter = 0;
int free_counter = 0;

// FOREST ENEMIES -----------------------------------------------------------------------------------------------------
const Enemy forest_enemies[] = {
{
    .name = "Slime",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
{
    .name = "Wolf",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
{
    .name = "Sapling",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
{
    .name = "Forest Elf",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
};

// CAVE ENEMIES -------------------------------------------------------------------------------------------------------
const Enemy cave_enemies[] = {
{
    .name = "Zombie",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
{
    .name = "Skeleton",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0 
},
{
    .name = "Spider",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
{
    .name = "Goblin",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
};

// CASTLE ENEMIES -----------------------------------------------------------------------------------------------------
const Enemy castle_enemies[] = {
{
    .name = "Cursed Knight",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
{
    .name = "Necromancer",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
{
    .name = "Cultist",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
{
    .name = "Sorcerer",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
},
};

// BOSSES ---------------------------------------------------------------------------------------------------------
const Enemy forest_boss = {
    .name = "Fire Dragon",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

const Enemy cave_boss = {
    .name = "Stone Guardian",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

const Enemy castle_boss = {
    .name = "Evil Wizard",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};