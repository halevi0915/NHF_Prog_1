#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "visual.h"

#include "globals.h"
#include "logic.h"

// INIT SCREEN --------------------------------------------------------------------------------------------------------

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
void middle(int row, char* msg, int is_dynamic) {
    int msg_len = strlen(msg);
    int x_pos = (WIDTH / 2) - (msg_len / 2);
    mvprintw(row, x_pos, "%s", msg);
    if (is_dynamic) {free(msg); ++free_counter;}
}

// az adott sor két szélére irja a két msg-t (ha csak egyik oldalra irunk a masik ures)
void side(int row, char* msg_1, char* msg_2, int is_dynamic_1, int is_dynamic_2) {
    mvprintw(row, 3, "%s", msg_1);                              // 3-al beljebb a draw_base elferese miatt
    mvprintw(row, WIDTH - (3 + strlen(msg_2)), "%s", msg_2);    // es WIDTH - 3
    if (is_dynamic_1) {free(msg_1); ++free_counter;}
    if (is_dynamic_2) {free(msg_2); ++free_counter;}
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

// megrajzolja az alap kinézetet - statok
void draw_header(Game* game_ptr) {
    side(2, "WIZARD", "", 0, 0);
    side(3, format_string("LVL %d", game_ptr->player.lvl), "", 1, 0);
    side(4, format_string("%d/%d EXP", game_ptr->player.exp, game_ptr->player.next_level_exp), "", 1, 0);
    side(5, format_string("%d/%d HP", game_ptr->player.hp, game_ptr->player.max_hp), "", 1, 0);
    side(6, format_string("%d/%d MANA", game_ptr->player.mana, game_ptr->player.max_mana), "", 1, 0);

    side(2, "", format_string("%s", game_ptr->enemy.name), 0, 1);
    side(3, "", format_string("%d/%d HP", game_ptr->enemy.hp, game_ptr->enemy.max_hp), 0, 1);
    side(4, "", format_string("%d DEF", game_ptr->enemy.armor), 0, 1);
    side(5, "", format_string("%d EXP", game_ptr->enemy.exp_reward), 0, 1);
    line(10);
}

// WRAPPERS -----------------------------------------------------------------------------------------------------------

typedef void (*draw_menu)(int x);
typedef void (*draw_game)(int x, Game* game_ptr);
typedef void (*draw_msg)(char* msg, int is_dynamic, Game* game_ptr);

// clear - draw base - refresh combo
void menu_wrapper(draw_menu func, int x) {
    clear();
    draw_base();
    func(x);
    refresh();
}

void game_wrapper(draw_game func, int x, Game* game_ptr) {
    clear();
    draw_base();
    draw_header(game_ptr);
    func(x, game_ptr);
    refresh();
}

void msg_wrapper(draw_msg func, char* msg, int is_dynamic, Game* game_ptr) {
    clear();
    draw_base();
    draw_header(game_ptr);
    func(msg, is_dynamic, game_ptr);
    refresh();
}

// MENU DRAW ----------------------------------------------------------------------------------------------------------

void main_menu_draw(int x) {
    middle(3, "Journey of the Wizard", 0);
    middle(HEIGHT - 10, "+-----------+", 0);
    middle(HEIGHT - 9,"| by:Profit |", 0);
    line(HEIGHT - 8);
    (x % 3 == 0) ? side(HEIGHT - 6, " > START GAME", "", 0, 0) : side(HEIGHT - 6, "   START GAME", "", 0, 0);
    (x % 3 == 1) ? side(HEIGHT - 5, " > LOAD GAME", "", 0, 0) : side(HEIGHT - 5, "   LOAD GAME", "", 0, 0);
    (x % 3 == 2) ? side(HEIGHT - 4, " > QUIT", "", 0, 0) : side(HEIGHT - 4, "   QUIT", "", 0, 0);
}

void quit_menu_draw(int x) {
    middle(3, "Are you sure?", 0);
    line(HEIGHT - 8);
    (x % 2 == 0) ? side(HEIGHT - 5, " > YES", "", 0, 0) : side(HEIGHT - 5, "   YES", "", 0, 0);
    (x % 2 == 1) ? side(HEIGHT - 4, " > NO", "", 0, 0) : side(HEIGHT - 4, "   NO", "", 0, 0);
}

void diff_menu_draw(int x) {
    middle(3, "Select a difficulty!", 0);
    line(HEIGHT - 8);
    (x % 3 == 0) ? side(HEIGHT - 6, " > EASY", "", 0, 0) : side(HEIGHT - 6, "   EASY", "", 0, 0);
    (x % 3 == 1) ? side(HEIGHT - 5, " > NORMAL", "", 0, 0) : side(HEIGHT - 5, "   NORMAL", "", 0, 0);
    (x % 3 == 2) ? side(HEIGHT - 4, " > HARD", "", 0, 0) : side(HEIGHT - 4, "   HARD", "", 0, 0);
}

void pause_menu_draw(int x) {
    middle(3, "Game is Paused", 0);
    line(HEIGHT - 8);
    (x % 3 == 0) ? side(HEIGHT - 6, " > RESUME", "", 0, 0) : side(HEIGHT - 6, "   RESUME", "", 0, 0);
    (x % 3 == 1) ? side(HEIGHT - 5, " > SAVE", "", 0, 0) : side(HEIGHT - 5, "   SAVE", "", 0, 0);
    (x % 3 == 2) ? side(HEIGHT - 4, " > MAIN MENU", "", 0, 0) : side(HEIGHT - 4, "   MAIN MENU", "", 0, 0);
}

void debug_draw(int x, Game* game_ptr) {
    switch (x % 3) {
        case 0:
            middle(3, format_string("turn: %d", game_ptr->turn), 1);
            middle(4, format_string("stage: %d", game_ptr->stage), 1);
            middle(5, format_string("diff: %f", game_ptr->diff), 1);
            break;
        case 1:
            middle(3, format_string("lvl: %d", game_ptr->player.lvl), 1);
            middle(4, format_string("exp: %d", game_ptr->player.exp), 1);
            middle(5, format_string("next_level_exp: %d", game_ptr->player.next_level_exp), 1);
            middle(6, format_string("max_hp: %d", game_ptr->player.max_hp), 1);
            middle(7, format_string("hp: %d", game_ptr->player.hp), 1);
            middle(8, format_string("max_mana: %d", game_ptr->player.max_mana), 1);
            middle(9, format_string("mana: %d", game_ptr->player.mana), 1);
            middle(10, format_string("armor: %d", game_ptr->player.armor), 1);
            middle(11, format_string("zap_cost: %d", game_ptr->player.zap_cost), 1);
            middle(12, format_string("zap_dmg: %d", game_ptr->player.zap_dmg), 1);
            middle(13, format_string("charge_cost: %d", game_ptr->player.charge_cost), 1);
            middle(14, format_string("charge_up: %d", game_ptr->player.charge_up), 1);
            middle(15, format_string("meteor_cost: %d", game_ptr->player.meteor_cost), 1);
            middle(16, format_string("meteor_dmg: %d", game_ptr->player.meteor_dmg), 1);
            middle(17, format_string("meteor_fire: %d", game_ptr->player.meteor_fire), 1);
            middle(18, format_string("heal_potion: %d", game_ptr->player.heal_potion), 1);
            break;
        case 2:
            middle(3, format_string("name: %s", game_ptr->enemy.name), 1);
            middle(4, format_string("max_hp: %d", game_ptr->enemy.dmg), 1);
            middle(5, format_string("max_hp: %d", game_ptr->enemy.max_hp), 1);
            middle(6, format_string("hp: %d", game_ptr->enemy.hp), 1);
            middle(7, format_string("armor: %d", game_ptr->enemy.armor), 1);
            middle(8, format_string("exp_reward: %d", game_ptr->enemy.exp_reward), 1);
            middle(9, format_string("fire: %d", game_ptr->enemy.fire), 1);
            break;
    }
    line(HEIGHT - 8);
    (x % 3 == 0) ? side(HEIGHT - 6, " > GAME", "", 0, 0) : side(HEIGHT - 6, "   GAME", "", 0, 0);
    (x % 3 == 1) ? side(HEIGHT - 5, " > PLAYER", "", 0, 0) : side(HEIGHT - 5, "   PLAYER", "", 0, 0);
    (x % 3 == 2) ? side(HEIGHT - 4, " > ENEMY", "", 0, 0) : side(HEIGHT - 4, "   ENEMY", "", 0, 0);
}

void game_action_draw(int x, Game* game_ptr) {
    line(HEIGHT - 10);
    (x % 5 == 0) ? side(HEIGHT - 8, " > ZAP", "", 0, 0) : side(HEIGHT - 8, "   ZAP", "", 0, 0);
    (x % 5 == 1) ? side(HEIGHT - 7, " > OVERCHARGE", "", 0, 0) : side(HEIGHT - 7, "   OVERCHARGE", "", 0, 0);
    (x % 5 == 2) ? side(HEIGHT - 6, " > METEOR SHOWER", "", 0, 0) : side(HEIGHT - 6, "   METEOR SHOWER", "", 0, 0);
    (x % 5 == 3) ? side(HEIGHT - 5, " > HEAL", "", 0, 0) : side(HEIGHT - 5, "   HEAL", "", 0, 0);
    (x % 5 == 4) ? side(HEIGHT - 4, " > REST", "", 0, 0) : side(HEIGHT - 4, "   REST", "", 0, 0);
}

void game_msg_draw(char* msg, int is_dynamic, Game* game_ptr) {
    if (is_dynamic) middle(12, msg, 1);
    else middle(12, msg, 0);
    line(HEIGHT - 10);
    middle(HEIGHT - 8, "< Press Space >", 0);
}

void game_over_draw(int x, Game* game_ptr) {
    middle(3, "Game Over", 0);
    middle(5, format_string("stage: %d", game_ptr->stage), 1);
    line(HEIGHT - 10);
    middle(HEIGHT - 8, "< Main menu >", 0);
}

// MENUS --------------------------------------------------------------------------------------------------------------

int main_menu() {
    int x = 0;
    int option_count = 3;
    char key;
    while (true) {
        menu_wrapper(main_menu_draw, x);
        key = getch();
        switch (key) {
            case 'w': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
        }
    }
    
}

int quit_menu() {
    int x = 0;
    int option_count = 2;
    char key;
    while (true) {
        menu_wrapper(quit_menu_draw, x);
        key = getch();
        switch (key) {
            case 'w': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
        }
    }
}

float diff_menu() {
    int x = 0;
    int option_count = 3;
    char key;
    while (true) {
        menu_wrapper(diff_menu_draw, x);
        key = getch();
        switch (key) {
            case 'w': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n':
                switch (x) {
                    case 0: return easy_diff_mult;
                    case 1: return normal_diff_mult;
                    case 2: return hard_diff_mult;
            }
        }
    }
}

int pause_menu() {
    int x = 0;
    int option_count = 3;
    char key;
    while (true) {
        menu_wrapper(pause_menu_draw, x);
        key = getch();
        switch (key) {
            case 'w': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
            case 27: //esc
                return 0; // resume
        }
    }
}

void debug(Game* game_ptr) {
    int x = 0;
    int option_count = 3;
    char key;
    int running = true;
    while (running) {
        game_wrapper(debug_draw, x, game_ptr);
        key = getch();
        switch (key) {
            case 'w': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': running = false; break;
        }
    }
    
}

int game_action(Game* game_ptr) {
    int x = 0;
    int option_count = 5;
    char key;
    while (true) {
        game_wrapper(game_action_draw, x, game_ptr);
        key = getch();
        switch (key) {
            case 'w': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
            case 27: //esc
                return -1; // for pause menu
        }
    }
    
}

void game_msg(char* msg, int is_dynamic, Game* game_ptr) {
    char key;
    msg_wrapper(game_msg_draw, msg, is_dynamic, game_ptr);
    while (true) {
        key = getch();
        if (key == ' ') break;
    }
    
}

void game_over(Game* game_ptr) {
    char key;
    game_wrapper(game_over_draw, 0, game_ptr);
    while (true) {
        key = getch();
        if (key == ' ') break;
    }
    
}