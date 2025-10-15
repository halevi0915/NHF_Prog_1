#include "menus.h"
#include "visual.h"

// MAIN_MENU

int main_menu() {
    int x = 0;
    char key;
    menu_wrapper(main_menu_draw, x);
    while (true) {
        key = getch();
        switch (key) {
        case 'w':                               // felfele lépünk x csökken
            x = (x > 0) ? (x - 1) : 1;
            break;
        case 's':                               // lefele lépünk x novekedik
            x = (x < 1) ? (x + 1) : 0;
            break;
        case '\n':                              // '\n' accept és return
            return x;
        }
        menu_wrapper(main_menu_draw, x);
    }
    
}

