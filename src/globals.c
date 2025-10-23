#include "globals.h"

// player
typedef struct Player {
    int lvl;                // 1
    int exp;                // 0
    int next_level_exp;     // 10 

    int max_hp;             // 100
    int hp;
    int hp_regen;           // 0

    int max_mana;           // 200
    int mana;
    int mana_regen;         // 0

    int armor;              // 0

    int zap_cost;           // 20
    int zap_dmg;            // 10

    int charge_cost;        // 40
    int charge_up;          // 1

    int meteor_cost;        // 100
    int meteor_dmg;         // 50
    int meteor_fire;        // 1

    int heal_potion;        // 3
} Player;

// enemy
typedef struct Enemy {
    char name[20];
    int dmg;
    int max_hp;
    int hp;
    int armor;
    int exp_reward;
    int fire;
} Enemy;

// game
typedef struct Game {      // default value
    Player player;      // default player from globals
    Enemy enemy;        
    int turn;           // player: 0 enemy: 1
    int stage;          // forest: 0 cave: 1 castle: 2 default: 0
    float diff;         // easy: 0.8 normal: 1 hard: 1.6 (enemy stat multiplier)
} Game;

// globals
int heal_amount = 40;
int enemy_heal_amount = 10;
int fire_dmg = 10;

// difficulty multipilers - enemy statokon változtat
float easy_diff_mult = 0.8;
float normal_diff_mult = 1;
float hard_diff_mult = 1.6;

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
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy forest_enemy_2 = {
    .name = "Wolf",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy forest_enemy_3 = {
    .name = "Sapling",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy forest_enemy_4 = {
    .name = "Forest Elf",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// mid-game enemies - CAVE
Enemy cave_enemy_1 = {
    .name = "Zombie",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy cave_enemy_2 = {
    .name = "Skeleton",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0 
};

Enemy cave_enemy_3 = {
    .name = "Spider",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy cave_enemy_4 = {
    .name = "Goblin",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// end-game enemies -  CASTLE

Enemy castle_enemy_1 = {
    .name = "Cursed Knight",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy castle_enemy_2 = {
    .name = "Necromancer",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy castle_enemy_3 = {
    .name = "Cultist",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

Enemy castle_enemy_4 = {
    .name = "Sorcerer",
    .dmg = 10,
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
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// CAVE boss
Enemy cave_boss = {
    .name = "Stone Guardian",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};

// DEMONIC CASTLE boss
Enemy castle_boss = {
    .name = "Evil Wizard",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .exp_reward = 10,
    .fire = 0
};