#include "globals.h"

// GLOBALS ------------------------------------------------------------------------------------------------------------
const int heal_amount = 40;
const int enemy_heal_amount = 20;
const int rest_amount = 50;
const int fire_dmg = 10;
const int charge_mult = 2;
const float enemy_heal_threshold = 0.3;
const int enemy_per_stage = 4;
const int stage_count = 3;
const int exp_scale = 10;
const float diff_scale = 1.2;

const float easy_diff_mult = 0.8;
const float normal_diff_mult = 1;
const float hard_diff_mult = 1.6;

int malloc_counter = 0;
int free_counter = 0;

// FOREST ENEMIES -----------------------------------------------------------------------------------------------------
const Enemy forest_enemies[] = {
{
    .name = "Slime",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 20,
    .crit_dmg = 1.6,
    .miss_ch = 20,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
{
    .name = "Wolf",
    .dmg = 10,
    .max_hp = 10,
    .hp = 10,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
{
    .name = "Sapling",
    .dmg = 10,
    .max_hp = 10,
    .hp = 10,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
{
    .name = "Forest Elf",
    .dmg = 10,
    .max_hp = 10,
    .hp = 10,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
};

// CAVE ENEMIES -------------------------------------------------------------------------------------------------------
const Enemy cave_enemies[] = {
{
    .name = "Zombie",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
{
    .name = "Skeleton",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0, 
},
{
    .name = "Spider",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
{
    .name = "Goblin",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
};

// CASTLE ENEMIES -----------------------------------------------------------------------------------------------------
const Enemy castle_enemies[] = {
{
    .name = "Cursed Knight",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
{
    .name = "Necromancer",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
{
    .name = "Cultist",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
{
    .name = "Sorcerer",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
},
};

// BOSSES -------------------------------------------------------------------------------------------------------------
const Enemy forest_boss = {
    .name = "Fire Dragon",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
};

const Enemy cave_boss = {
    .name = "Stone Guardian",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
};

const Enemy castle_boss = {
    .name = "Evil Wizard",
    .dmg = 10,
    .max_hp = 100,
    .hp = 100,
    .armor = 10,
    .crit_ch = 10,
    .crit_dmg = 1.6,
    .miss_ch = 10,
    .exp_reward = 10,
    .fire = 0,
    .stun = 0,
};

// VOICE LINES --------------------------------------------------------------------------------------------------------

// const char* zap_msg[] = {
//     "Enemy jolted! (%d dmg)",
//     "Shocked! (%d dmg)",
//     "A bolt strikes! (%d dmg)",
//     "Struck by lightning! (%d dmg)",
//     "Electrified! (%d dmg)",
//     "Hit with a spark! (%d dmg)",
//     "Touched by thunder! (%d dmg)",
//     "Current hits the target! (%d dmg)",
//     "Lightning arcs! (%d dmg)",
//     "A jolt of energy! (%d dmg)",
//     "Hit with electric force! (%d dmg)",
//     "Shocker! (%d dmg)",
//     "Zap attack lands! (%d dmg)",
//     "Enemy feels the spark! (%d dmg)",
//     "Bolted! (%d dmg)",
//     "Hit by a spark blast! (%d dmg)",
//     "Crackling energy! (%d dmg)",
//     "Struck with voltage! (%d dmg)",
// };

// const char* charge_msg[] = {
//     "Wand is charging! (%dx)",
//     "Energy gathers! (%dx)",
//     "Power surges through the wand! (%dx)",
//     "Gathering magical force! (%dx)",
//     "The wand hums with energy! (%dx)",
//     "Spell power increasing! (%dx)",
//     "Charging complete! (%dx)",
//     "Arcane energy flows! (%dx)",
//     "Magic intensifies! (%dx)",
//     "Power builds! (%dx)",
//     "Wand glows brightly! (%dx)",
//     "Energy is focused! (%dx)",
//     "The air crackles with power! (%dx)",
//     "A surge of magic! (%dx)",
//     "Force concentrates! (%dx)",
//     "Spell energy accumulating! (%dx)",
//     "Wand pulses with power! (%dx)",
//     "Charging spell! (%dx)",
//     "Energy locked and ready! (%dx)",
//     "Power at maximum! (%dx)"
// };

// const char* meteor_msg[] = {
//     "Meteor lands! (%d dmg)",
//     "Fiery impact! (%d dmg)",
//     "Burned by a falling star! (%d dmg)",
//     "The sky crashes down! (%d dmg)",
//     "Meteor hits! (%d dmg)",
//     "Crashing inferno! (%d dmg)",
//     "Enemy engulfed in fire! (%d dmg)",
//     "Impact from above! (%d dmg)",
//     "Fallen star strikes! (%d dmg)",
//     "Meteor smash! (%d dmg)",
//     "Inferno rains down! (%d dmg)",
//     "Hit by a fireball! (%d dmg)",
//     "Flame impact! (%d dmg)",
//     "Burning meteorfall! (%d dmg)",
//     "Sky fire! (%d dmg)",
//     "Explosive impact! (%d dmg)"
// };

// const char* heal_msg[] = {
//     "Health restored! (+%d hp)",
//     "Feeling better! (+%d hp)",
//     "Wounds begin to close! (+%d hp)",
//     "Healing magic takes effect! (+%d hp)",
//     "Vitality returns! (+%d hp)",
//     "The potion works! (+%d hp)",
//     "Life flows anew! (+%d hp)",
//     "Recovered some strength! (+%d hp)",
//     "Energy renewed! (+%d hp)",
//     "Health replenished! (+%d hp)",
//     "The potion soothes your body! (+%d hp)",
//     "Feeling revitalized! (+%d hp)",
//     "Restored to full health! (+%d hp)",
//     "Life force surges! (+%d hp)",
//     "The healing takes hold! (+%d hp)",
//     "Wounds knit together! (+%d hp)",
//     "Strength returns! (+%d hp)",
//     "You feel rejuvenated! (+%d hp)",
//     "Potion restores vitality! (+%d hp)",
//     "Vitality courses through you! (+%d hp)",
// };

// const char* rest_msg[] = {
//     "Mana restored! (+%d mana)",
//     "Energy returns! (+%d mana)",
//     "Magic flowing again! (+%d mana)",
//     "The mind clears, power returns! (+%d mana)",
//     "Magical reserves replenished! (+%d mana)",
//     "Feeling magically recharged! (+%d mana)",
//     "Arcane energy restored! (+%d mana)",
//     "Power wells up within! (+%d mana)",
//     "Mana flows through you! (+%d mana)",
//     "Energy renewed! (+%d mana)",
//     "Your focus strengthens! (+%d mana)",
//     "Spell power returning! (+%d mana)",
//     "Resting restores your magic! (+%d mana)",
//     "Magical energy courses through you! (+%d mana)",
//     "The mind and mana recover! (+%d mana)",
//     "Recharged and ready! (+%d mana)",
//     "Your magical essence returns! (+%d mana)",
//     "Mana bubbling back! (+%d mana)",
//     "Magic returns to full strength! (+%d mana)",
// };

// const char* burn_msg[] = {
//     "Enemy scorched! (%d dmg)",
//     "Burning! (%d dmg)",
//     "Engulfed in flames! (%d dmg)",
//     "Searing heat strikes! (%d dmg)",
//     "Enemy ablaze! (%d dmg)",
//     "Catches fire! (%d dmg)",
//     "Flames lick the enemy! (%d dmg)",
//     "On fire! (%d dmg)",
//     "Charred! (%d dmg)",
//     "The flames consume! (%d dmg)",
//     "Blazing! (%d dmg)",
//     "Enemy torched! (%d dmg)",
//     "Fire burns bright! (%d dmg)",
//     "Engulfed in a fiery blast! (%d dmg)",
//     "Enemy takes burn damage! (%d dmg)",
//     "Cinders fly! (%d dmg)",
//     "Scorched by fire! (%d dmg)",
//     "Flames sear through! (%d dmg)",
//     "Enemy writhes in fire! (%d dmg)",
// };

// const char* enemy_atk_msg[] = {
//     "Enemy strikes! (%d dmg)",
//     "Enemy attacks! (%d dmg)",
//     "A blow lands! (%d dmg)",
//     "Enemy swings! (%d dmg)",
//     "Incoming attack! (%d dmg)",
//     "Hit by the enemy! (%d dmg)",
//     "Enemy lunges! (%d dmg)",
//     "A strike from the foe! (%d dmg)",
//     "Enemy charges! (%d dmg)",
//     "Enemy slashes! (%d dmg)",
//     "Enemy hits hard! (%d dmg)",
//     "The foe delivers a blow! (%d dmg)",
//     "Enemy smashes! (%d dmg)",
//     "Enemy claws! (%d dmg)",
//     "A sudden attack! (%d dmg)",
//     "The enemy lashes out! (%d dmg)",
//     "Enemy thrusts forward! (%d dmg)",
//     "The foe strikes fast! (%d dmg)",
//     "Enemy crushes! (%d dmg)",
//     "A ferocious strike! (%d dmg)"
// };

// const char* enemy_heal_msg[] = {
//     "Enemy recovers! (+%d hp)",
//     "Healing magic at work! (+%d hp)",
//     "Enemy restored some health! (+%d hp)",
//     "Wounds begin to close! (+%d hp)",
//     "Enemy regenerates! (+%d hp)",
//     "Healing energy surrounds the foe! (+%d hp)",
//     "Enemy feels renewed! (+%d hp)",
//     "The foe recovers strength! (+%d hp)",
//     "Health returns to the enemy! (+%d hp)",
//     "Enemy revitalized! (+%d hp)",
//     "The enemy mends! (+%d hp)",
//     "Restoration magic hits the foe! (+%d hp)",
//     "Enemy rejuvenates! (+%d hp)",
//     "Wounds knit together! (+%d hp)",
//     "Enemy gains vitality! (+%d hp)",
//     "The foe's health improves! (+%d hp)",
//     "Healing flows into the enemy! (+%d hp)",
//     "Enemy recovers vigor! (+%d hp)",
//     "The foe’s wounds close! (+%d hp)",
//     "The enemy restores vitality! (+%d hp)"
// };