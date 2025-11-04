#ifndef GLOBALS_H
#define GLOBALS_H

extern const int enemy_heal_amount;
extern const int fire_dmg;
extern const int charge_mult;
extern const float enemy_heal_threshold;
extern const int enemy_per_stage;
extern const int stage_count;
extern const int exp_scale;
extern const float diff_scale;

extern const int armor_cap;
extern const int dodge_cap;

extern const float easy_diff_mult;
extern const float normal_diff_mult;
extern const float hard_diff_mult;

extern int malloc_counter;
extern int free_counter;

typedef struct ItemBase {
    char name[20];
    int stat_id;
    int boost;
    int boost_min;
    int boost_max;
} ItemBase;

typedef struct Item {
    char name[20];
    int stat_id;
    int boost;
} Item;

typedef struct Inventory {
    int size;
    Item* contents;
} Inventory;

typedef struct Player {
    char name[20];
    int lvl;
    int exp;
    int next_level_exp;
    int exp_boost;          // id 1
    int heal_potion;        // id 2
    Inventory inventory;

    int max_hp;             // id 3
    int hp;
    int heal_amount;        // id 4

    int max_mana;           // id 5
    int mana;
    int rest_amount;        // id 6

    int armor;              // id 7
    int crit_ch;            // id 8
    int crit_dmg;           // id 9
    int miss_ch;            // id 10
    int dodge_ch;           // id 11

    int zap_cost;           // id 12
    int zap_dmg;            // id 13
    int zap_stun_ch;        // id 14

    int charge_cost;        // id 15
    int charge_up;          // id 16
    int current_charge;

    int meteor_cost;        // id 17
    int meteor_dmg;         // id 18
    int meteor_fire;        // id 19
} Player;

typedef struct Enemy {
    char name[20];
    int dmg;
    int max_hp;
    int hp;
    int armor;
    int crit_ch;
    int crit_dmg;
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

extern const ItemBase common_items[];
extern const ItemBase rare_items[];
extern const ItemBase epic_items[];
extern const ItemBase legendary_items[];

// extern const char* zap_msg[];
// extern const char* charge_msg[];
// extern const char* meteor_msg[];
// extern const char* heal_msg[];
// extern const char* rest_msg[];
// const char* burn_msg[];
// const char* enemy_atk_msg[];
// const char* enemy_heal_msg[];

#endif