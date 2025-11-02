#ifndef GLOBALS_H
#define GLOBALS_H

extern const int heal_amount;
extern const int enemy_heal_amount;
extern const int rest_amount;
extern const int fire_dmg;
extern const int charge_mult;
extern const float enemy_heal_threshold;
extern const int enemy_per_stage;
extern const int stage_count;
extern const int exp_scale;
extern const float diff_scale;

extern const float easy_diff_mult;
extern const float normal_diff_mult;
extern const float hard_diff_mult;

extern int free_counter;
extern int malloc_counter;

typedef struct Player {
    int lvl;
    int exp;
    int next_level_exp;

    int max_hp;
    int hp;

    int max_mana;
    int mana;

    int armor;
    int crit_ch;
    float crit_dmg;
    int miss_ch;

    int zap_cost;
    int zap_dmg;
    int zap_stun_ch;

    int charge_cost;
    int charge_up;
    int current_charge;

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
    int crit_ch;
    float crit_dmg;
    int miss_ch;
    int exp_reward;
    int fire;
    int stun;
} Enemy;

typedef struct Game {
    Player player;
    Enemy enemy;        
    int turn;
    int stage;
    int enemy_index;
    float diff;
    int is_story;
} Game;

extern const Enemy forest_enemies[];
extern const Enemy cave_enemies[];
extern const Enemy castle_enemies[];

extern const Enemy forest_boss;
extern const Enemy cave_boss;
extern const Enemy castle_boss;

// extern const char* zap_msg[];
// extern const char* charge_msg[];
// extern const char* meteor_msg[];
// extern const char* heal_msg[];
// extern const char* rest_msg[];
// const char* burn_msg[];
// const char* enemy_atk_msg[];
// const char* enemy_heal_msg[];

#endif