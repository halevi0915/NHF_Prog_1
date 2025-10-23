#include <ncurses.h>
#include <stdbool.h>

#include "visual.h"
#include "game.h"

int main() {
    init_screen();

    int running = true;

    while (running) {
        int main_result = main_menu(); // 0: start_game 1: load_game 2: quit_game    
        switch (main_result) {
            case 0:
                float diff = diff_menu();
                Game game = init_new_game(diff);
                debug(game);
                break;
            // case 1:
            //     int load_result = load_game()
            //     break;
            case 2:
                int quit_result = quit_menu(); // 0: yes 1: no
                running = quit_result;
                break;
        }
    }
    endwin();
    return 0;
}