#ifndef PLAYER_H
#define PLAYER_H

typedef struct p {
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

#endif