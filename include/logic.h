#ifndef LOGIC_H
#define LOGIC_H

#include "globals.h"

int max(int a, int b);
int min(int a, int b);
int randint(int start, int end);
int calc_chance(const int chance);
char* format_string(const char* format, ...);
char* bar_string(const char* text, const int current_value, const int max_value);

#endif