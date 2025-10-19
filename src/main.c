#include <ncurses.h>

#include "visual.h"
#include "menus.h"
#include "game.h"

int main() {
    init_screen();

    int main_result;
    int play_result;
    int load_result;
    int quit_result;
    int running = 1;

    while (running) {
        main_result = main_menu(); // 0: start 1: load_game 2: quit_game    
        switch (main_result) {
            case 0:
                Game game = start_new_game();
                debug(game);
                //play_result = 
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