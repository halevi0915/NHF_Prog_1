#include "debugmalloc.h"
#include "curses.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "game.h"
#include "visual.h"
#include "logic.h"


// main modul:
//     - inicializálja a megjelenítést: init_screen()
//     - lefoglal egy game strukturát és majd abba tölti az új/betöltött game-et
//     - addig futtat egy loop-ot amig a felhasználó nem lép ki: program_running = quit_menu()
//     - a loopban a főmenü visszatérési értéke alapján:
//         - létrehoz egy új játékot és elindítja azt
//         - betölt egy mentést és elindítja azt
//         - meghívja a kilépés menüt amiben ha a felhasználó yes-t választ, kilép a loop-bol
//     - megjelenítést be kell fejezni: endwin()

int main() {
    init_screen();
    srand(time(NULL));
    int program_running = 1;
    Game* game_ptr = (Game*)malloc(sizeof(Game));
    if (game_ptr == NULL) {perror("game_ptr alloc error"); exit(1);};

    while (program_running) {
        switch (main_menu()) {  // 0: start_game 1: load_game 2: quit_game
            case 0:
                create_new_game(game_ptr);
                game_loop(game_ptr);
                break;
            case 1:
                if (save_exists(save_name)) {
                    if (load_game(game_ptr, save_name)) {
                        game_loop(game_ptr);
                    }
                }
                break;
            case 2: program_running = quit_menu(); break; // 0: yes 1: no 
        }
    }
    free(game_ptr);
    endwin();
    return 0;
}