#ifndef LOGIC_H
#define LOGIC_H

#include "globals.h"

int max(int a, int b);
int min(int a, int b);
int randint(int start, int end);
bool calc_chance(const int chance);
char* format_string(const char* format, ...);
char* bar_string(const char* text, const int current_value, const int max_value);
void save_game(Game* game_ptr, const char* filename);
bool load_game(Game* game_ptr, const char* filename);
bool save_exists(const char* file_name);

#endif