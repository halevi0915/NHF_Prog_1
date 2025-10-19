#include "enemy.h"

typedef struct e {
    char name[20];
    int max_hp;
    int hp;
    int armor;
    int exp_reward;
    int fire;

} Enemy;

Enemy reset_enemy(Enemy e) {
    e.hp = e.max_hp;
    e.fire = 0;
    return e;
}

Enemy scale_enemy(Enemy e, float diff) {
    e.max_hp *= diff;
    e.hp = e.max_hp * diff;
    e.armor *= diff;
    e.exp_reward *= (1 / diff);
    return e;
}