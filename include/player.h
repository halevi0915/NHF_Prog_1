#ifndef PLAYER_H
#define PLAYER_H

typedef struct p {
    int lvl;                // 1
    int exp;
    int next_level_exp;             // 

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

#endif