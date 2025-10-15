#include <ncurses.h>

#include "visual.h"
#include "menus.h"

int main() {
    init_screen();

    int alma = main_menu();    
    printf("%d", alma);

    endwin();
    return 0;
}