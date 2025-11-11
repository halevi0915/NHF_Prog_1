#ifndef GLOBALS_H
#define GLOBALS_H

// game
extern const float easy_diff_mult;
extern const float normal_diff_mult;
extern const float hard_diff_mult;
extern const float diff_scale;

extern const int stage_count;
extern const int enemy_per_stage;

// player
extern const int exp_scale;
extern const int fire_dmg;
extern const int charge_mult;
extern const int armor_cap;
extern const int dodge_cap;

// enemy
extern const int enemy_heal_amount;
extern const int enemy_heal_threshold;

typedef enum Colors {
    WHITE = 1,
    RED,
    GREEN,
    BLUE,
    YELLOW
} Colors;

typedef enum Stats {
    exp_boost,
    heal_potion,
    max_hp,
    heal_amount,
    max_mana,
    rest_amount,
    armor,
    crit_ch,
    crit_dmg,
    miss_ch,
    dodge_ch,
    zap_cost,
    zap_dmg,
    zap_stun_ch,
    charge_cost,
    charge_up,
    meteor_cost,
    meteor_dmg,
    meteor_fire
} Stats;

typedef struct ItemBase {
    char name[20];
    Stats stat_id;
    int boost;
    int boost_min;
    int boost_max;
} ItemBase;

typedef struct Item {
    char name[20];
    Stats stat_id;
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
    int exp_boost;          // id 0
    int heal_potion;        // id 1
    Inventory inventory;

    int max_hp;             // id 2
    int hp;
    int heal_amount;        // id 3

    int max_mana;           // id 4
    int mana;
    int rest_amount;        // id 5

    int armor;              // id 6
    int crit_ch;            // id 7
    int crit_dmg;           // id 8
    int miss_ch;            // id 9
    int dodge_ch;           // id 10

    int zap_cost;           // id 11
    int zap_dmg;            // id 12
    int zap_stun_ch;        // id 13

    int charge_cost;        // id 14
    int charge_up;          // id 15
    int current_charge;

    int meteor_cost;        // id 16
    int meteor_dmg;         // id 17
    int meteor_fire;        // id 18
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