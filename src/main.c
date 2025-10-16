#include <ncurses.h>

#include "visual.h"
#include "menus.h"

int main() {
    init_screen();

    int main_result;
    int play_result;
    int load_result;
    int quit_result;
    int running;

    while (running) {

    main_result = main_menu(); // 0: play 1: quit_game    
    switch (main_result) {
    case 0:
        //play_result = start_game();
        break;
    // case 1:
    //     load_result = load_game()
    //     break;
    case 2:
        quit_result = quit_menu(); // 0: yes 1: no
        running = quit_result;
        break;
    }
    }
    endwin();
    return 0;
}