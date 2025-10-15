#include "visual.h"

// INIT SCREEN

int HEIGHT, WIDTH;

void init_screen() {
    // INIT
    initscr();                                      // stdscr a default screen pointer, nem kell elmenteni kulon

    // SETTINGS
    cbreak();                                       // instant input - dosent buffer
    noecho();                                       // noecho
    curs_set(0);                                    // invisible curzor
    keypad(stdscr, TRUE);                           // nyilakhoz kell
    nodelay(stdscr, FALSE);                         // blocking input: getch() waits for next input and doesnt give err

    // COLOR
    if (has_colors()) {                             // ha van color support
        start_color();                              // init color
        init_pair(1, COLOR_WHITE, COLOR_BLACK);     // parokba rendezi a szineket, id-kel lehet kesobb hivatkozni ra
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
    }
    attron(COLOR_PAIR(1));                          // default legyen a fekete

    // ECT
    clear();                                        // clears the screen
    getmaxyx(stdscr, HEIGHT, WIDTH);                // returns screen size
}

// SCREEN TOOLS -------------------------------------------------------------------------------------------------------

// az adott sorra egy vonalat rajzol
void line(int row) {
    char t[WIDTH+1];                                        // +1 for \0
    int middle_len = (WIDTH - 2 > 0) ? (WIDTH - 2) : 0;     // -2 for the 2 '|'

    // FILL
    t[0] = '|';
    for (int i = 0; i < middle_len; i++)
        t[1 + i] = '-';
    t[1 + middle_len] = '|';
    t[2 + middle_len] = '\0';

    // OUT
    mvprintw(row, 0, "%s", t);
}

// az adott sor közepére irja az msg-t
void middle(int row, char msg[]) {
    int msg_len = strlen(msg);
    int x_pos = (WIDTH / 2) - (msg_len / 2);
    mvprintw(row, x_pos, "%s", msg);
}

// az adott sor két szélére irja a két msg-t (ha csak egyik oldalra irunk a masik ures)
void side(int row, char msg_1[], char msg_2[]) {
    mvprintw(row, 3, "%s", msg_1);                              // 3-al beljebb a draw_base elferese miatt
    mvprintw(row, WIDTH - (3 + strlen(msg_2)), "%s", msg_2);    // es WIDTH - 3
}

// megrajzolja az alap kinézetet
// vonalak minden oldalon
void draw_base() {
    line(1);
    line(HEIGHT - 2);
    for (int i = 0; i < HEIGHT; ++i) {
        mvprintw(i, 2, "%s", "|");
        mvprintw(i, WIDTH - 3, "%s", "|");
    }
}

// WRAPPER ------------------------------------------------------------------------------------------------------------

typedef void (*draw_menu)(int x);

// egy wrapper minden menuhoz hogy clear-draw_base aztan refresh
void menu_wrapper(draw_menu func, int x) {
    clear();
    draw_base();
    func(x);
    refresh();
}

// MENUS --------------------------------------------------------------------------------------------------------------

void main_menu_draw(int x) {
    middle(3,"IMMORTAL COMBAT");
    middle(4,"by:Profit");
    line(HEIGHT - 5);
    (x % 2 == 0) ? side(HEIGHT - 4, " > START", "") : side(HEIGHT - 4, "   START", "");
    (x % 2 == 1) ? side(HEIGHT - 3, " > QUIT", "") : side(HEIGHT - 3, "   QUIT", "");
}