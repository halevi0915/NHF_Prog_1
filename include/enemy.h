#ifndef ENEMY_H
#define ENEMY_H

typedef struct e {
    char name[20];
    int max_hp;
    int hp;
    int armor;
    int exp_reward;
    int fire;
} Enemy;

Enemy reset_enemy(Enemy e);
Enemy scale_enemy(Enemy e, float diff);

#endif