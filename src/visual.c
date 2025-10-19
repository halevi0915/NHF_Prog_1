#include "visual.h"
#include "game.h"
#include "logic.h"

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
    int middle_len = (WIDTH - 6 > 0) ? (WIDTH - 6) : 0;     // -6 for the 2 '|'

    // FILL
    t[0] = ' ';
    t[1] = ' ';
    t[2] = '|';
    for (int i = 0; i < middle_len; i++)
        t[3 + i] = '-';
    t[3 + middle_len] = '|';
    t[4 + middle_len] = ' ';
    t[5 + middle_len] = ' ';
    t[6 + middle_len] = '\0';

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

// megrajzolja az alap kinézetet - vonalak minden oldalon
void draw_base() {
    for (int i = 0; i < HEIGHT; ++i) {
        mvprintw(i, 2, "%s", "|");
        mvprintw(i, WIDTH - 3, "%s", "|");
    }
    line(1);
    line(HEIGHT - 2);
}

// WRAPPER ------------------------------------------------------------------------------------------------------------

typedef void (*draw_menu)(int x);
typedef void (*draw_game)(int x, Game game);

// clear - draw base - refresh combp
void menu_wrapper(draw_menu func, int x) {
    clear();
    draw_base();
    func(x);
    refresh();
}

void game_wrapper(draw_game func, int x, Game game) {
    clear();
    draw_base();
    func(x, game);
    refresh();
}

// MENUS --------------------------------------------------------------------------------------------------------------

void main_menu_draw(int x) {
    middle(3, "Journey of the Wizard");
    middle(HEIGHT - 10, "+-----------+");
    middle(HEIGHT - 9,"| by:Profit |");
    line(HEIGHT - 8);
    (x % 3 == 0) ? side(HEIGHT - 6, " > START GAME", "") : side(HEIGHT - 6, "   START GAME", "");
    (x % 3 == 1) ? side(HEIGHT - 5, " > LOAD GAME", "") : side(HEIGHT - 5, "   LOAD GAME", "");
    (x % 3 == 2) ? side(HEIGHT - 4, " > QUIT", "") : side(HEIGHT - 4, "   QUIT", "");
}

void quit_menu_draw(int x) {
    middle(3, "Are you sure?");
    line(HEIGHT - 8);
    (x % 2 == 0) ? side(HEIGHT - 5, " > YES", "") : side(HEIGHT - 5, "   YES", "");
    (x % 2 == 1) ? side(HEIGHT - 4, " > NO", "") : side(HEIGHT - 4, "   NO", "");
}

void diff_menu_draw(int x) {
    middle(3, "Select a difficulty!");
    line(HEIGHT - 8);
    (x % 3 == 0) ? side(HEIGHT - 6, " > EASY", "") : side(HEIGHT - 6, "   EASY", "");
    (x % 3 == 1) ? side(HEIGHT - 5, " > NORMAL", "") : side(HEIGHT - 5, "   NORMAL", "");
    (x % 3 == 2) ? side(HEIGHT - 4, " > HARD", "") : side(HEIGHT - 4, "   HARD", "");
}

void debug_draw(int x, Game game) {
    switch (x % 3) {
        case 0:
            middle(3, format_str_int("turn: %d", game.turn));
            middle(4, format_str_int("stage: %d", game.stage));
            middle(5, format_str_int("diff: %d", game.diff));
            break;
        case 1:
            middle(3, format_str_int("lvl: %d", game.player.lvl));
            middle(4, format_str_int("exp: %d", game.player.exp));
            middle(5, format_str_int("next_level_exp: %d", game.player.next_level_exp));
            middle(6, format_str_int("max_hp: %d", game.player.max_hp));
            middle(7, format_str_int("hp: %d", game.player.hp));
            middle(8, format_str_int("hp_regen: %d", game.player.hp_regen));
            middle(9, format_str_int("max_mana: %d", game.player.max_mana));
            middle(10, format_str_int("mana: %d", game.player.mana));
            middle(11, format_str_int("mana_regen: %d", game.player.mana_regen));
            middle(12, format_str_int("armor: %d", game.player.armor));
            middle(13, format_str_int("zap_cost: %d", game.player.zap_cost));
            middle(14, format_str_int("zap_dmg: %d", game.player.zap_dmg));
            middle(15, format_str_int("charge_cost: %d", game.player.charge_cost));
            middle(16, format_str_int("charge_up: %d", game.player.charge_up));
            middle(17, format_str_int("meteor_cost: %d", game.player.meteor_cost));
            middle(18, format_str_int("meteor_dmg: %d", game.player.meteor_dmg));
            middle(19, format_str_int("meteor_fire: %d", game.player.meteor_fire));
            middle(20, format_str_int("heal_potion: %d", game.player.heal_potion));
            break;
        case 2:
            middle(3, format_str_str("name: %s", game.enemy.name));
            middle(4, format_str_int("max_hp: %d", game.enemy.max_hp));
            middle(5, format_str_int("hp: %d", game.enemy.hp));
            middle(6, format_str_int("armor: %d", game.enemy.armor));
            middle(7, format_str_int("exp_reward: %d", game.enemy.exp_reward));
            middle(8, format_str_int("fire: %d", game.enemy.fire));
            break;
    }
    line(HEIGHT - 8);
    (x % 3 == 0) ? side(HEIGHT - 6, " > GAME", "") : side(HEIGHT - 6, "   GAME", "");
    (x % 3 == 1) ? side(HEIGHT - 5, " > PLAYER", "") : side(HEIGHT - 5, "   PLAYER", "");
    (x % 3 == 2) ? side(HEIGHT - 4, " > ENEMY", "") : side(HEIGHT - 4, "   ENEMY", "");
}