#ifndef GLOBALS_H
#define GLOBALS_H

typedef struct Player {
    int lvl;
    int exp;
    int next_level_exp;

    int max_hp;
    int hp;
    int hp_regen;

    int max_mana;
    int mana;
    int mana_regen;

    int armor;

    int zap_cost;
    int zap_dmg;

    int charge_cost;
    int charge_up;

    int meteor_cost;
    int meteor_dmg;
    int meteor_fire;

    int heal_potion;
} Player;

typedef struct Enemy {
    char name[20];
    int dmg;
    int max_hp;
    int hp;
    int armor;
    int exp_reward;
    int fire;
} Enemy;

typedef struct Game {
    Player player;
    Enemy enemy;
    int turn;
    int stage;
    float diff;
} Game;

extern int heal_amount;
extern int enemy_heal_amount;
extern int fire_dmg;

extern float easy_diff_mult;
extern float normal_diff_mult;
extern float hard_diff_mult;

extern Player default_player;

extern Enemy forest_enemy_1;
extern Enemy forest_enemy_2;
extern Enemy forest_enemy_3;
extern Enemy forest_enemy_4;

extern Enemy cave_enemy_1;
extern Enemy cave_enemy_2;
extern Enemy cave_enemy_3;
extern Enemy cave_enemy_4;

extern Enemy castle_enemy_1;
extern Enemy castle_enemy_2;
extern Enemy castle_enemy_3;
extern Enemy castle_enemy_4;

extern Enemy forest_boss;
extern Enemy cave_boss;
extern Enemy castle_boss;

#endif