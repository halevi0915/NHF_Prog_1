#include "menus.h"
#include "visual.h"

// MAIN_MENU

int main_menu() {
    int x = 0;
    int max_option = 2;                         // hany opcio van -1
    char key;
    menu_wrapper(main_menu_draw, x);
    while (true) {
        key = getch();
        switch (key) {
        case 'w':                               // felfele lépünk x csökken
            x = (x > 0) ? (x - 1) : max_option;
            break;
        case 's':                               // lefele lépünk x novekedik
            x = (x < max_option) ? (x + 1) : 0;
            break;
        case '\n':                              // '\n' accept és return
            return x;
        }
        menu_wrapper(main_menu_draw, x);
    }
    
}

int quit_menu() {
    int x = 0;
    int max_option = 1;                         // hany opcio van -1
    char key;
    menu_wrapper(quit_menu_draw, x);
    while (true) {
        key = getch();
        switch (key) {
        case 'w':                               // felfele lépünk x csökken
            x = (x > 0) ? (x - 1) : max_option;
            break;
        case 's':                               // lefele lépünk x novekedik
            x = (x < max_option) ? (x + 1) : 0;
            break;
        case '\n':                              // '\n' accept és return
            return x;
        }
        menu_wrapper(quit_menu_draw, x);
    }
    
}

