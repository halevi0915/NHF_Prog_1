#include "globals.h"

// GLOBALS ------------------------------------------------------------------------------------------------------------
// game
const float easy_diff_mult = 1.0;
const float normal_diff_mult = 1.5;
const float hard_diff_mult = 2.0;
const float diff_scale = 1.5;
const char save_name[] = "save.game";

const int stage_count = 3;
const int enemy_per_stage = 4;

// player
const int exp_scale = 10;
const int fire_dmg = 10;
const int charge_mult = 2;
const int armor_cap = 80;
const int dodge_cap = 80;

// enemy
const int enemy_heal_amount = 5;
const int enemy_heal_threshold = 30;

// sys
int malloc_counter = 0;
int free_counter = 0;

// FOREST ENEMIES -----------------------------------------------------------------------------------------------------
const Enemy forest_enemies[] = {
{
    .name = "Slime",
    .dmg = 10,
    .max_hp = 10,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 2000,
},
{
    .name = "Wolf",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
},
{
    .name = "Sapling",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
},
{
    .name = "Forest Elf",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
}
};

// CAVE ENEMIES -------------------------------------------------------------------------------------------------------
const Enemy cave_enemies[] = {
{
    .name = "Zombie",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
},
{
    .name = "Skeleton",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20, 
},
{
    .name = "Spider",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
},
{
    .name = "Goblin",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
}
};

// CASTLE ENEMIES -----------------------------------------------------------------------------------------------------
const Enemy castle_enemies[] = {
{
    .name = "Cursed Knight",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
},
{
    .name = "Necromancer",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
},
{
    .name = "Cultist",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
},
{
    .name = "Sorcerer",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
}
};

// BOSSES -------------------------------------------------------------------------------------------------------------
const Enemy forest_boss = {
    .name = "Fire Dragon",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
};

const Enemy cave_boss = {
    .name = "Stone Guardian",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
};

const Enemy castle_boss = {
    .name = "Evil Wizard",
    .dmg = 10,
    .max_hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 15,
    .exp_reward = 20,
};

// ITEMS --------------------------------------------------------------------------------------------------------------

const ItemBase common_items[] = {
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

const ItemBase rare_items[] = {
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

const ItemBase epic_items[] = {
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

const ItemBase legendary_items[] = {
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