#include "globals.h"

// GLOBALS ------------------------------------------------------------------------------------------------------------
// game
const float easy_diff_mult = 1.0;
const float normal_diff_mult = 1.5;
const float hard_diff_mult = 2.0;
const float diff_scale = 1.5;           // multiplies the diff when going to a new stage
const char save_name[] = "save.game";

const int stage_count = 3;
const int enemy_per_stage = 4;          // number of enemies before a boss

// player
const int exp_scale = 10;               // added to the next_lvl_exp when lvl up
const int fire_dmg = 10;                // fire_dmg
const int charge_mult = 2;              // damage mult par charge: 1charge 2x, 2charge 4x
const int armor_cap = 80;               // hard limit for player armor
const int dodge_cap = 80;               // hard limit for player dodge_ch

// enemy
const int enemy_heal_amount = 5;        // scales with diff
const int enemy_heal_threshold = 30;    // the % under which the enemy heals