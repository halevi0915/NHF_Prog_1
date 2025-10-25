#ifndef VISUAL_H
#define VISUAL_H

#include "globals.h"

extern int HEIGHT;
extern int WIDTH;

void init_screen();

int main_menu();
int quit_menu();
float diff_menu();
int pause_menu();

void debug(Game* game);
int game_action(Game* game);
void game_msg(char* msg, bool is_dynamic, Game* game);

#endif
