#include "curses.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "game.h"
#include "visual.h"

/*
main modul:
    - inicializálja a megjelenítést: init_screen()
    - addig futtat egy loop-ot amig a felhasználó nem lép ki: program_running = quit_menu()
    - a loopban a főmenü visszatérési értéke alapján:
        - létrehoz egy új játékot és elindítja azt
        - (WIP) betölt egy mentést és elindítja azt
        - meghívja a kilépés menüt amiben ha a felhasználó yes-t választ, kilép a loop-bol
    - a végén a megjelenítést be kell fejezni: endwin()
*/
int main() {
    init_screen();
    srand(time(NULL));
    int program_running = 1;
    Game game;

    while (program_running) {
        switch (main_menu()) {  // 0: start_game 1: load_game 2: quit_game
            case 0:
                game = create_new_game();
                game_loop(&game);
                break;
            case 1:
                // if (save_present()) game = load_game();
                break;
            case 2: program_running = quit_menu(); break; // 0: yes 1: no 
        }
    }
    //printf("%d malloc\n", malloc_counter);
    //printf("%d free\n", free_counter);
    endwin();
    return 0;
}