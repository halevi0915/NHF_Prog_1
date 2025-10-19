#include "player.h"
#include "logic.h"

typedef struct p {
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

// Player heal(Player p, float diff) {
//     if (p.heal_potion > 0 | p.hp < p.max_hp) {
//         p.hp = max(p.hp + (40 * (1/diff)), p.max_hp);
//         p.heal_potion -= 1;
//         return p;
//     }
//     else return p;
// }