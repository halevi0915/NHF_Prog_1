#ifndef VISUAL_H
#define VISUAL_H

#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

#include "globals.h"
#include "logic.h"

extern int HEIGHT;
extern int WIDTH;

//init
void init_screen();

//tools
void line(int row);
void middle(int row, char msg[]);
void side(int row, char msg_1[], char msg_2[]);
void draw_base();

//wrapper
typedef void (*draw_menu)(int x);
void menu_wrapper(draw_menu func, int x);

typedef void (*draw_game)(int x, Game game);
void game_wrapper(draw_game func, int x, Game game);

typedef void (*draw_game_msg)(char* msg, Game game);
void game_msg_wrapper(draw_game_msg func, char* msg, Game game);

//menu draw
void main_menu_draw(int x);
void quit_menu_draw(int x);
void diff_menu_draw(int x);

void debug_draw(int x, Game game);
void game_action_draw(int x, Game game);
void game_msg_draw(char* msg, Game game);

// menu logic
int main_menu();
int quit_menu();
float diff_menu();

int debug(Game game);
int game_action(Game game);
int game_msg(char* msg, Game game);

#endif
