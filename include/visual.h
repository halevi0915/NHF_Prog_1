#ifndef VISUAL_H
#define VISUAL_H

#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

#include "globals.h"
#include "logic.h"

extern int HEIGHT;
extern int WIDTH;

void init_screen();

int main_menu();
int quit_menu();
float diff_menu();

void debug(Game* game);
int game_action(Game* game);
int game_msg(char* msg, Game* game);

#endif
