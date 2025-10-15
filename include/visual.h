#ifndef VISUAL_H
#define VISUAL_H

#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

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

//menus
void main_menu_draw(int x);

#endif
