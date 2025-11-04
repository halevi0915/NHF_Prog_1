#include "debugmalloc.h"

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
    keypad(stdscr, TRUE);                           // nyilakhoz kell (nincs hasznalva)
    nodelay(stdscr, FALSE);                         // blocking input: getch() waits for next input and doesnt give err

    // COLOR
    // if (has_colors()) {                             // ha van color support
    //     start_color();                              // init color
    //     init_pair(1, COLOR_WHITE, COLOR_BLACK);     // parokba rendezi a szineket, id-kel lehet kesobb hivatkozni ra
    //     init_pair(2, COLOR_RED, COLOR_BLACK);
    //     init_pair(3, COLOR_GREEN, COLOR_BLACK);
    //     init_pair(4, COLOR_BLUE, COLOR_BLACK);
    // }
    // attron(COLOR_PAIR(1));                          // default legyen a fekete feher

    // ECT
    clear();                                        // clears the screen
    getmaxyx(stdscr, HEIGHT, WIDTH);                // returns screen size
}

// SCREEN TOOLS -------------------------------------------------------------------------------------------------------

// az adott sorra egy vonalat rajzol
void line(const int row) {
    char t[WIDTH+1];                                        // +1 for \0
    int middle_len = (WIDTH - 6 > 0) ? (WIDTH - 6) : 0;     // -6 for the 2 '|'

    // FILL
    t[0] = ' ';
    t[1] = ' ';
    t[2] = '|';
    for (int i = 0; i < middle_len; i++)
        t[3 + i] = '_';
    t[3 + middle_len] = '|';
    t[4 + middle_len] = ' ';
    t[5 + middle_len] = ' ';
    t[6 + middle_len] = '\0';

    // OUT
    mvprintw(row, 0, "%s", t);
}

// az adott sor közepére irja az msg-t
void middle(const int row, char* msg, const int is_dynamic) {
    int msg_len = strlen(msg);
    int x_pos = (WIDTH / 2) - (msg_len / 2);
    mvprintw(row, x_pos, "%s", msg);
    if (is_dynamic) {free(msg); ++free_counter;}
}

// az adott sor két szélére irja a két msg-t (ha csak egyik oldalra irunk a masik ures)
void side(const int row, char* msg_1, char* msg_2, const int is_dynamic_1, const int is_dynamic_2) {
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
    char sector_separator_left[WIDTH / 3 + 1 - 4]; // -4 adjusting / kerekities
    char sector_separator_right[WIDTH / 3 + 1 - 4];
    char sector_line_left[WIDTH / 3 + 1 - 4];
    char sector_line_right[WIDTH / 3 + 1 - 4];

    sector_separator_right[0] = '|';
    sector_line_right[0] = '|';
    for (int i = 0; i < WIDTH / 3 - 4; ++i) {
        sector_separator_left[i] = ' ';
        sector_separator_right[i+1] = ' ';
        sector_line_left[i] = '_';
        sector_line_right[i+1] = '_';
    }
    sector_separator_left[WIDTH / 3 - 4] = '|';
    sector_line_left[WIDTH / 3 - 4] = '|';

    sector_separator_left[WIDTH / 3 + 1 - 4] = '\0';
    sector_separator_right[WIDTH / 3 + 1 - 4] = '\0';
    sector_line_left[WIDTH / 3 + 1 - 4] = '\0';
    sector_line_right[WIDTH / 3 + 1 - 4] = '\0';

    for (int i = 2; i < HEIGHT - 9; ++i) {side(i, sector_separator_left, sector_separator_right, 0, 0);}

    // player sector
    side(3, format_string(" LVL %d  < %s >", game_ptr->player.lvl, game_ptr->player.name), "", 1, 0);
    side(4, sector_line_left, sector_line_right, 0, 0);

    side(6, format_string("                                  CRIT   %d%% - %.1fx", game_ptr->player.crit_ch, (game_ptr->player.crit_dmg / 10.0)), "", 1, 0);
    side(7, format_string("                                  DODGE  %d%%", game_ptr->player.dodge_ch), "", 1, 0);
    side(8, format_string("                                  CHARGE %dx", game_ptr->player.current_charge), "", 1, 0);
    side(9, format_string("                                  HEAL   %dx", game_ptr->player.heal_potion), "", 1, 0);

    side(6, format_string("                  %d/%d", game_ptr->player.exp, game_ptr->player.next_level_exp), "", 1, 0);
    side(7, format_string("                  %d/%d", game_ptr->player.hp, game_ptr->player.max_hp), "", 1, 0);
    side(8, format_string("                  %d/%d", game_ptr->player.mana, game_ptr->player.max_mana), "", 1, 0);
    
    side(6, bar_string(" EXP ", game_ptr->player.exp, game_ptr->player.next_level_exp), "", 1, 0);
    side(7, bar_string(" HP  ", game_ptr->player.hp, game_ptr->player.max_hp), "", 1, 0);
    side(8, bar_string(" MP  ", game_ptr->player.mana, game_ptr->player.max_mana), "", 1, 0);
    side(9, format_string(" DEF %d%% ", game_ptr->player.armor), "", 1, 0);

    side(10, sector_line_left, "", 0, 0);
    side(21, sector_line_left, "", 0, 0);
    side(23, " < Inventory >", "", 0, 0);
    for (int i = 0; i < game_ptr->player.inventory.size; ++i) {
        side(i + 24, format_string(" %s (%d)", game_ptr->player.inventory.contents[i].name, game_ptr->player.inventory.contents[i].boost), "", 1, 0);
    }

    // enemy sector
    if (game_ptr->enemy.hp == 0) side(3, "", format_string("Dead - < %s > ", game_ptr->enemy.name), 0, 1);
    else if (game_ptr->enemy.stun == 1) side(3, "", format_string("Stunned - < %s > ", game_ptr->enemy.name), 0, 1);
    else if (game_ptr->enemy.fire > 0) side(3, "", format_string("Burning - < %s > ", game_ptr->enemy.name), 0, 1);
    else side(3, "", format_string("< %s > ", game_ptr->enemy.name), 0, 1);

    side(6, "", format_string("HP %d/%d             ", game_ptr->enemy.hp, game_ptr->enemy.max_hp), 0, 1);
    side(6, "", bar_string("", game_ptr->enemy.hp, game_ptr->enemy.max_hp), 0, 1);

    side(7, "", format_string("DEF %d%% ", game_ptr->enemy.armor), 0, 1);
    side(8, "", format_string("EXP %d ", game_ptr->enemy.exp_reward), 0, 1);

    side(9, "", sector_line_right, 0, 0);

    // middle sector
    middle(3, format_string("Stage: %d", game_ptr->stage), 1);
    middle(4, format_string("Difficulty: %.2f", game_ptr->diff), 1);
    middle(5, format_string("Boss in %d!", enemy_per_stage - game_ptr->enemy_index + 1), 1);
}   

// WRAPPERS -----------------------------------------------------------------------------------------------------------

typedef void (*draw_menu)(const int* x);
typedef void (*draw_game)(const int* x, Game* game_ptr);
typedef void (*draw_msg)(char* msg, const int is_dynamic, Game* game_ptr);
typedef void (*draw_item)(const int* x, const Item* items, Game* game_ptr);

// clear - draw base - refresh combo
void menu_wrapper(draw_menu func, const int* x) {
    clear();
    draw_base();
    func(x);
    refresh();
}

void game_wrapper(draw_game func, const int* x, Game* game_ptr) {
    clear();
    draw_base();
    draw_header(game_ptr);
    func(x, game_ptr);
    refresh();
}

void msg_wrapper(draw_msg func, char* msg, const int is_dynamic, Game* game_ptr) {
    clear();
    draw_base();
    draw_header(game_ptr);
    func(msg, is_dynamic, game_ptr);
    refresh();
}

void item_wrapper(draw_item func, const int* x, const Item* items, Game* game_ptr) {
    clear();
    draw_base();
    draw_header(game_ptr);
    func(x, items, game_ptr);
    refresh();
}

// MENU DRAW ----------------------------------------------------------------------------------------------------------

void main_menu_draw(const int* x) {
    middle(3, "Journey of the Wizard", 0);
    middle(HEIGHT - 14, "+-----------+", 0);
    middle(HEIGHT - 13,"| by:Profit |", 0);
    line(HEIGHT - 12);
    switch (*x % 3) {
        case 0:
            side(HEIGHT - 10, "_________________________", "", 0, 0);
            side(HEIGHT - 9, "             START NEW  /", "", 0, 0);
            side(HEIGHT - 8, "_______________________/", "", 0, 0);
            side(HEIGHT - 7, "       LOAD SAVE  /", "", 0, 0);
            side(HEIGHT - 6, "_________________/", "", 0, 0);
            side(HEIGHT - 5, "          QUIT  /", "", 0, 0);
            side(HEIGHT - 4, "_______________/", "", 0, 0);
            break;
        case 1:
            side(HEIGHT - 10, "_____________________", "", 0, 0);
            side(HEIGHT - 9, "         START NEW  /", "", 0, 0);
            side(HEIGHT - 8, "___________________/___", "", 0, 0);
            side(HEIGHT - 7, "           LOAD SAVE  /", "", 0, 0);
            side(HEIGHT - 6, "_____________________/", "", 0, 0);
            side(HEIGHT - 5, "          QUIT  /", "", 0, 0);
            side(HEIGHT - 4, "_______________/", "", 0, 0);
            break;
        case 2:
            side(HEIGHT - 10, "_____________________", "", 0, 0);
            side(HEIGHT - 9, "         START NEW  /", "", 0, 0);
            side(HEIGHT - 8, "___________________/", "", 0, 0);
            side(HEIGHT - 7, "       LOAD SAVE  /", "", 0, 0);
            side(HEIGHT - 6, "_________________/___", "", 0, 0);
            side(HEIGHT - 5, "              QUIT  /", "", 0, 0);
            side(HEIGHT - 4, "___________________/", "", 0, 0);
            break;
    }
}

void quit_menu_draw(const int* x) {
    middle(3, "Are you sure?", 0);
    line(HEIGHT - 12);
    switch (*x % 2) {
        case 0:
            side(HEIGHT - 9, "_________________________", "", 0, 0);
            side(HEIGHT - 8, "                   YES  /", "", 0, 0);
            side(HEIGHT - 7, "_______________________/", "", 0, 0);
            side(HEIGHT - 6, "              NO  /", "", 0, 0);
            side(HEIGHT - 5, "_________________/", "", 0, 0);
            break;
        case 1:
            side(HEIGHT - 9, "_____________________", "", 0, 0);
            side(HEIGHT - 8, "               YES  /", "", 0, 0);
            side(HEIGHT - 7, "___________________/___", "", 0, 0);
            side(HEIGHT - 6, "                  NO  /", "", 0, 0);
            side(HEIGHT - 5, "_____________________/", "", 0, 0);
            break;
    }
}

void diff_menu_draw(const int* x) {
    middle(3, "Select a difficulty!", 0);
    line(HEIGHT - 12);
    switch (*x % 3) {
        case 0:
            side(HEIGHT - 10, "_________________________", "", 0, 0);
            side(HEIGHT - 9, "                  EASY  /", "", 0, 0);
            side(HEIGHT - 8, "_______________________/", "", 0, 0);
            side(HEIGHT - 7, "          NORMAL  /", "", 0, 0);
            side(HEIGHT - 6, "_________________/", "", 0, 0);
            side(HEIGHT - 5, "          HARD  /", "", 0, 0);
            side(HEIGHT - 4, "_______________/", "", 0, 0);
            break;
        case 1:
            side(HEIGHT - 10, "_____________________", "", 0, 0);
            side(HEIGHT - 9, "              EASY  /", "", 0, 0);
            side(HEIGHT - 8, "___________________/___", "", 0, 0);
            side(HEIGHT - 7, "              NORMAL  /", "", 0, 0);
            side(HEIGHT - 6, "_____________________/", "", 0, 0);
            side(HEIGHT - 5, "          HARD  /", "", 0, 0);
            side(HEIGHT - 4, "_______________/", "", 0, 0);
            break;
        case 2:
            side(HEIGHT - 10, "_____________________", "", 0, 0);
            side(HEIGHT - 9, "              EASY  /", "", 0, 0);
            side(HEIGHT - 8, "___________________/", "", 0, 0);
            side(HEIGHT - 7, "          NORMAL  /", "", 0, 0);
            side(HEIGHT - 6, "_________________/___", "", 0, 0);
            side(HEIGHT - 5, "              HARD  /", "", 0, 0);
            side(HEIGHT - 4, "___________________/", "", 0, 0);
            break;
    }
}

void pause_menu_draw(const int* x) {
    middle(3, "Game is Paused", 0);
    line(HEIGHT - 12);
    switch (*x % 3) {
        case 0:
            side(HEIGHT - 10, "_________________________", "", 0, 0);
            side(HEIGHT - 9, "                RESUME  /", "", 0, 0);
            side(HEIGHT - 8, "_______________________/", "", 0, 0);
            side(HEIGHT - 7, "            SAVE  /", "", 0, 0);
            side(HEIGHT - 6, "_________________/", "", 0, 0);
            side(HEIGHT - 5, "     MAIN MENU  /", "", 0, 0);
            side(HEIGHT - 4, "_______________/", "", 0, 0);
            break;
        case 1:
            side(HEIGHT - 10, "_____________________", "", 0, 0);
            side(HEIGHT - 9, "            RESUME  /", "", 0, 0);
            side(HEIGHT - 8, "___________________/___", "", 0, 0);
            side(HEIGHT - 7, "                SAVE  /", "", 0, 0);
            side(HEIGHT - 6, "_____________________/", "", 0, 0);
            side(HEIGHT - 5, "     MAIN MENU  /", "", 0, 0);
            side(HEIGHT - 4, "_______________/", "", 0, 0);
            break;
        case 2:
            side(HEIGHT - 10, "_____________________", "", 0, 0);
            side(HEIGHT - 9, "            RESUME  /", "", 0, 0);
            side(HEIGHT - 8, "___________________/", "", 0, 0);
            side(HEIGHT - 7, "            SAVE  /", "", 0, 0);
            side(HEIGHT - 6, "_________________/___", "", 0, 0);
            side(HEIGHT - 5, "         MAIN MENU  /", "", 0, 0);
            side(HEIGHT - 4, "___________________/", "", 0, 0);
            break;
    }
}

void game_over_draw(const int* x) {
    middle(3, "Game Over", 0);
    line(HEIGHT - 12);
    middle(HEIGHT - 8, "< Main menu >", 0);
}

// void debug_draw(const int* x, Game* game_ptr) {
//     switch (*x % 3) {
//         case 0:
//             middle(3, format_string("turn: %d", game_ptr->turn), 1);
//             middle(4, format_string("stage: %d", game_ptr->stage), 1);
//             middle(5, format_string("diff: %f", game_ptr->diff), 1);
//             break;
//         case 1:
//             middle(3, format_string("lvl: %d", game_ptr->player.lvl), 1);
//             middle(4, format_string("exp: %d", game_ptr->player.exp), 1);
//             middle(5, format_string("next_level_exp: %d", game_ptr->player.next_level_exp), 1);
//             middle(6, format_string("max_hp: %d", game_ptr->player.max_hp), 1);
//             middle(7, format_string("hp: %d", game_ptr->player.hp), 1);
//             middle(8, format_string("max_mana: %d", game_ptr->player.max_mana), 1);
//             middle(9, format_string("mana: %d", game_ptr->player.mana), 1);
//             middle(10, format_string("armor: %d", game_ptr->player.armor), 1);
//             middle(11, format_string("zap_cost: %d", game_ptr->player.zap_cost), 1);
//             middle(12, format_string("zap_dmg: %d", game_ptr->player.zap_dmg), 1);
//             middle(13, format_string("charge_cost: %d", game_ptr->player.charge_cost), 1);
//             middle(14, format_string("charge_up: %d", game_ptr->player.charge_up), 1);
//             middle(15, format_string("meteor_cost: %d", game_ptr->player.meteor_cost), 1);
//             middle(16, format_string("meteor_dmg: %d", game_ptr->player.meteor_dmg), 1);
//             middle(17, format_string("meteor_fire: %d", game_ptr->player.meteor_fire), 1);
//             middle(18, format_string("heal_potion: %d", game_ptr->player.heal_potion), 1);
//             break;
//         case 2:
//             middle(3, format_string("name: %s", game_ptr->enemy.name), 1);
//             middle(4, format_string("max_hp: %d", game_ptr->enemy.dmg), 1);
//             middle(5, format_string("max_hp: %d", game_ptr->enemy.max_hp), 1);
//             middle(6, format_string("hp: %d", game_ptr->enemy.hp), 1);
//             middle(7, format_string("armor: %d", game_ptr->enemy.armor), 1);
//             middle(8, format_string("exp_reward: %d", game_ptr->enemy.exp_reward), 1);
//             middle(9, format_string("fire: %d", game_ptr->enemy.fire), 1);
//             break;
//     }
//     line(HEIGHT - 8);
//     (*x % 3 == 0) ? side(HEIGHT - 6, " > GAME", "", 0, 0) : side(HEIGHT - 6, "   GAME", "", 0, 0);
//     (*x % 3 == 1) ? side(HEIGHT - 5, " > PLAYER", "", 0, 0) : side(HEIGHT - 5, "   PLAYER", "", 0, 0);
//     (*x % 3 == 2) ? side(HEIGHT - 4, " > ENEMY", "", 0, 0) : side(HEIGHT - 4, "   ENEMY", "", 0, 0);
// }

void game_action_draw(const int* x, Game* game_ptr) {
    line(HEIGHT - 9);
    switch (*x % 5) { // action desc
        case 0:
            side(12, " Lightning Zap", "", 0, 0);
            side(14, format_string(" - Dose %d damage", game_ptr->player.zap_dmg), "", 1, 0);
            side(15, format_string(" - Has %d%% chanche to stun the enemy", game_ptr->player.zap_stun_ch), "", 1, 0);
            side(16, format_string(" - Costs %d mana", game_ptr->player.zap_cost), "", 1, 0);
            side(19, " < Description >", "", 0, 0);
            side(20, " 'When you touch the wrong wire...' ", "", 0, 0);
            break;
        case 1:
            side(12, " Overcharged Wand", "", 0, 0);
            side(14, format_string(" - Charges your want up by %d", game_ptr->player.charge_up), "", 1, 0);
            side(15, format_string(" - Every charge gives an %d damage multipiler", charge_mult), "", 1, 0);
            side(16, format_string(" - Your wand is currently charged up by %d", game_ptr->player.current_charge), "", 1, 0);
            side(17, format_string(" - Costs %d mana", game_ptr->player.charge_cost), "", 1, 0);
            side(19, " < Description >", "", 0, 0);
            side(20, " 'Overclocking the wand!' ", "", 0, 0);
            break;
        case 2:
            side(12, " Meteor Shower", "", 0, 0);
            side(14, format_string(" - Dose %d damage", game_ptr->player.meteor_dmg), "", 1, 0);
            side(15, format_string(" - Sets the enemy on fire for %d turns", game_ptr->player.meteor_fire), "", 1, 0);
            side(16, format_string(" - Costs %d mana", game_ptr->player.meteor_cost), "", 1, 0);
            side(19, " < Description >", "", 0, 0);
            side(20, " 'Big rock goes brrr' ", "", 0, 0);
            break;
        case 3:
            side(12, " Heal Potion", "", 0, 0);
            side(14, format_string(" - Restores %d health", game_ptr->player.heal_amount), "", 1, 0);
            side(15, format_string(" - You currently have %d bottles", game_ptr->player.heal_potion), "", 1, 0);
            side(19, " < Description >", "", 0, 0);
            side(20, " 'Its not white monster i swear' ", "", 0, 0);
            break;
        case 4:
            side(12, " Rest", "", 0, 0);
            side(14, format_string(" - Restores %d mana", game_ptr->player.rest_amount), "", 1, 0);
            side(15, " - Unlimited use", "", 0, 0);
            side(19, " < Description >", "", 0, 0);
            side(20, " 'Quick power nap' ", "", 0, 0);
            break;
    }

    (*x % 5 == 0) ? side(HEIGHT - 7, " > [ ZAP ]", "", 0, 0) : side(HEIGHT - 7, "   [ ZAP ]", "", 0, 0);
    (*x % 5 == 1) ? side(HEIGHT - 6, " > [ CHARGE ]", "", 0, 0) : side(HEIGHT - 6, "   [ CHARGE ]", "", 0, 0);
    (*x % 5 == 2) ? side(HEIGHT - 5, " > [ METEOR ]", "", 0, 0) : side(HEIGHT - 5, "   [ METEOR ]", "", 0, 0);
    (*x % 5 == 3) ? side(HEIGHT - 4, " > [ HEAL ]", "", 0, 0) : side(HEIGHT - 4, "   [ HEAL ]", "", 0, 0);
    (*x % 5 == 4) ? side(HEIGHT - 3, " > [ REST ]", "", 0, 0) : side(HEIGHT - 3, "   [ REST ]", "", 0, 0);
}

void game_msg_draw(char* msg, const int is_dynamic, Game* game_ptr) {
    line(HEIGHT - 9);
    middle(HEIGHT - 10, msg, is_dynamic);
    middle(HEIGHT - 7, "< Press Space >", 0);
}

void game_item_draw(const int* x, const Item* items, Game* game_ptr) {
    line(HEIGHT - 9);
    (*x % 3 == 0) ? side(HEIGHT - 7, format_string(" > [ %s - %d ]", items[0].name, items[0].boost), "", 1, 0) : side(HEIGHT - 7, format_string("   [ %s - %d ]", items[0].name, items[0].boost), "", 1, 0);
    (*x % 3 == 1) ? side(HEIGHT - 6, format_string(" > [ %s - %d ]", items[1].name, items[1].boost), "", 1, 0) : side(HEIGHT - 6, format_string("   [ %s - %d ]", items[1].name, items[1].boost), "", 1, 0);
    (*x % 3 == 2) ? side(HEIGHT - 5, format_string(" > [ %s - %d ]", items[2].name, items[2].boost), "", 1, 0) : side(HEIGHT - 5, format_string("   [ %s - %d ]", items[2].name, items[2].boost), "", 1, 0);
}

// MENUS --------------------------------------------------------------------------------------------------------------

int main_menu() {
    int x = 0;
    int option_count = 3;
    char key;
    while (true) {
        menu_wrapper(main_menu_draw, &x);
        key = getch();
        switch (key) {
            case 'w': case 'W': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': case 'S': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
        }
    }
}

int quit_menu() {
    int x = 0;
    int option_count = 2;
    char key;
    while (true) {
        menu_wrapper(quit_menu_draw, &x);
        key = getch();
        switch (key) {
            case 'w': case 'W': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': case 'S': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
        }
    }
}

float diff_menu() {
    int x = 0;
    int option_count = 3;
    char key;
    while (true) {
        menu_wrapper(diff_menu_draw, &x);
        key = getch();
        switch (key) {
            case 'w': case 'W': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': case 'S': x = (x < option_count - 1) ? (x + 1) : 0; break;
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
        menu_wrapper(pause_menu_draw, &x);
        key = getch();
        switch (key) {
            case 'w': case 'W': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': case 'S': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
            case 27: //esc
                return 0; // resume
        }
    }
}

void game_over(Game* game_ptr) {
    char key;
    menu_wrapper(game_over_draw, NULL);
    while (true) {
        key = getch();
        if (key == ' ') break;
    }
}

// void debug(Game* game_ptr) {
//     int x = 0;
//     int option_count = 3;
//     char key;
//     int running = true;
//     while (running) {
//         game_wrapper(debug_draw, &x, game_ptr);
//         key = getch();
//         switch (key) {
//             case 'w': case 'W': x = (x > 0) ? (x - 1) : option_count - 1; break;
//             case 's': case 'S': x = (x < option_count - 1) ? (x + 1) : 0; break;
//             case '\n': running = false; break;
//         }
//     }
// }

int game_action(Game* game_ptr) {
    int x = 0;
    int option_count = 5;
    char key;
    while (true) {
        game_wrapper(game_action_draw, &x, game_ptr);
        key = getch();
        switch (key) {
            case 'w': case 'W': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': case 'S': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
            case 27: //esc
                return -1; // for pause menu
        }
    }
}

void game_msg(char* msg, const int is_dynamic, Game* game_ptr) {
    char key;
    msg_wrapper(game_msg_draw, msg, is_dynamic, game_ptr);
    while (true) {
        key = getch();
        if (key == ' ') break;
    }
}

int game_item(const Item* items, Game* game_ptr) {
    int x = 0;
    int option_count = 3;
    char key;
    while (true) {
        item_wrapper(game_item_draw, &x, items, game_ptr);
        key = getch();
        switch (key) {
            case 'w': case 'W': x = (x > 0) ? (x - 1) : option_count - 1; break;
            case 's': case 'S': x = (x < option_count - 1) ? (x + 1) : 0; break;
            case '\n': return x;
        }
    }
}