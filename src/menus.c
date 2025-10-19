#include "menus.h"
#include "visual.h"
#include "game.h"

// MAIN_MENU
// lehetne x % max_option - 1 a visszatérési érték és elég lenne az x hez hozzáadni és kivonni 1-et
// de igy nem lehet az int méretén túl menni

int main_menu() {
    int x = 0;
    int max_option = 2;
    char key;
    menu_wrapper(main_menu_draw, x);
    while (true) {
        key = getch();
        switch (key) {
        case 'w':
            x = (x > 0) ? (x - 1) : max_option;
            break;
        case 's':
            x = (x < max_option) ? (x + 1) : 0;
            break;
        case '\n':
            return x;
        }
        menu_wrapper(main_menu_draw, x);
    }
    
}

int quit_menu() {
    int x = 0;
    int max_option = 1;
    char key;
    menu_wrapper(quit_menu_draw, x);
    while (true) {
        key = getch();
        switch (key) {
        case 'w':
            x = (x > 0) ? (x - 1) : max_option;
            break;
        case 's':
            x = (x < max_option) ? (x + 1) : 0;
            break;
        case '\n':
            return x;
        }
        menu_wrapper(quit_menu_draw, x);
    }
    
}

int diff_menu() {
    int x = 0;
    int max_option = 2;
    char key;
    menu_wrapper(diff_menu_draw, x);
    while (true) {
        key = getch();
        switch (key) {
        case 'w':
            x = (x > 0) ? (x - 1) : max_option;
            break;
        case 's':
            x = (x < max_option) ? (x + 1) : 0;
            break;
        case '\n':
            return x;
        }
        menu_wrapper(diff_menu_draw, x);
    }

}

int debug(Game game) {
    int x = 0;
    int max_option = 3;
    char key;
    game_wrapper(debug_draw, x, game);
    while (true) {
        key = getch();
        switch (key) {
        case 'w':
            x = (x > 0) ? (x - 1) : max_option;
            break;
        case 's':
            x = (x < max_option) ? (x + 1) : 0;
            break;
        case '\n':
            return x;
        }
        game_wrapper(debug_draw, x, game);
    }
    
}

