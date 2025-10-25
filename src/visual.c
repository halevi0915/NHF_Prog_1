#include <stdbool.h>

#include "visual.h"

#include "globals.h"
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

void draw_header(Game* game_ptr) {
    side(2, "WIZARD", "");
    side(3, format_string("LVL %d", game_ptr->player.lvl), "");
    side(4, format_string("%d/%d EXP", game_ptr->player.exp, game_ptr->player.next_level_exp), "");
    side(5, format_string("%d/%d HP", game_ptr->player.hp, game_ptr->player.max_hp), "");
    side(6, format_string("%d/%d MANA", game_ptr->player.mana, game_ptr->player.max_mana), "");

    side(2, "", format_string("%s", game_ptr->enemy.name));
    side(3, "", format_string("%d/%d HP", game_ptr->enemy.hp, game_ptr->enemy.max_hp));
    side(4, "", format_string("%d DEF", game_ptr->enemy.armor));
    side(5, "", format_string("%d EXP", game_ptr->enemy.exp_reward));
    line(10);
}

// WRAPPER ------------------------------------------------------------------------------------------------------------

typedef void (*draw_menu)(void* value_ptr);
typedef void (*draw_game)(void* value_ptr, Game* game_ptr);

// clear - draw base - refresh combo
void menu_wrapper(draw_menu func, void* value_ptr) {
    clear();
    draw_base();
    func(value_ptr);
    refresh();
}

void game_wrapper(draw_game func, void* value_ptr, Game* game_ptr) {
    clear();
    draw_base();
    draw_header(game_ptr);
    func(value_ptr, game_ptr);
    refresh();
}

// MENUS --------------------------------------------------------------------------------------------------------------

void main_menu_draw(void* value_ptr) {
    int* x = (int*)value_ptr;
    middle(3, "Journey of the Wizard");
    middle(HEIGHT - 10, "+-----------+");
    middle(HEIGHT - 9,"| by:Profit |");
    line(HEIGHT - 8);
    (*x % 3 == 0) ? side(HEIGHT - 6, " > START GAME", "") : side(HEIGHT - 6, "   START GAME", "");
    (*x % 3 == 1) ? side(HEIGHT - 5, " > LOAD GAME", "") : side(HEIGHT - 5, "   LOAD GAME", "");
    (*x % 3 == 2) ? side(HEIGHT - 4, " > QUIT", "") : side(HEIGHT - 4, "   QUIT", "");
}

void quit_menu_draw(void* value_ptr) {
    int* x = (int*)value_ptr;
    middle(3, "Are you sure?");
    line(HEIGHT - 8);
    (*x % 2 == 0) ? side(HEIGHT - 5, " > YES", "") : side(HEIGHT - 5, "   YES", "");
    (*x % 2 == 1) ? side(HEIGHT - 4, " > NO", "") : side(HEIGHT - 4, "   NO", "");
}

void diff_menu_draw(void* value_ptr) {
    int* x = (int*)value_ptr;
    middle(3, "Select a difficulty!");
    line(HEIGHT - 8);
    (*x % 3 == 0) ? side(HEIGHT - 6, " > EASY", "") : side(HEIGHT - 6, "   EASY", "");
    (*x % 3 == 1) ? side(HEIGHT - 5, " > NORMAL", "") : side(HEIGHT - 5, "   NORMAL", "");
    (*x % 3 == 2) ? side(HEIGHT - 4, " > HARD", "") : side(HEIGHT - 4, "   HARD", "");
}

void debug_draw(void* value_ptr, Game* game_ptr) {
    int* x = (int*)value_ptr;
    switch (*x % 3) {
        case 0:
            middle(3, format_string("turn: %d", game_ptr->turn));
            middle(4, format_string("stage: %d", game_ptr->stage));
            middle(5, format_string("diff: %f", game_ptr->diff));
            break;
        case 1:
            middle(3, format_string("lvl: %d", game_ptr->player.lvl));
            middle(4, format_string("exp: %d", game_ptr->player.exp));
            middle(5, format_string("next_level_exp: %d", game_ptr->player.next_level_exp));
            middle(6, format_string("max_hp: %d", game_ptr->player.max_hp));
            middle(7, format_string("hp: %d", game_ptr->player.hp));
            middle(8, format_string("hp_regen: %d", game_ptr->player.hp_regen));
            middle(9, format_string("max_mana: %d", game_ptr->player.max_mana));
            middle(10, format_string("mana: %d", game_ptr->player.mana));
            middle(11, format_string("mana_regen: %d", game_ptr->player.mana_regen));
            middle(12, format_string("armor: %d", game_ptr->player.armor));
            middle(13, format_string("zap_cost: %d", game_ptr->player.zap_cost));
            middle(14, format_string("zap_dmg: %d", game_ptr->player.zap_dmg));
            middle(15, format_string("charge_cost: %d", game_ptr->player.charge_cost));
            middle(16, format_string("charge_up: %d", game_ptr->player.charge_up));
            middle(17, format_string("meteor_cost: %d", game_ptr->player.meteor_cost));
            middle(18, format_string("meteor_dmg: %d", game_ptr->player.meteor_dmg));
            middle(19, format_string("meteor_fire: %d", game_ptr->player.meteor_fire));
            middle(20, format_string("heal_potion: %d", game_ptr->player.heal_potion));
            break;
        case 2:
            middle(3, format_string("name: %s", game_ptr->enemy.name));
            middle(4, format_string("max_hp: %d", game_ptr->enemy.dmg));
            middle(5, format_string("max_hp: %d", game_ptr->enemy.max_hp));
            middle(6, format_string("hp: %d", game_ptr->enemy.hp));
            middle(7, format_string("armor: %d", game_ptr->enemy.armor));
            middle(8, format_string("exp_reward: %d", game_ptr->enemy.exp_reward));
            middle(9, format_string("fire: %d", game_ptr->enemy.fire));
            break;
    }
    line(HEIGHT - 8);
    (*x % 3 == 0) ? side(HEIGHT - 6, " > GAME", "") : side(HEIGHT - 6, "   GAME", "");
    (*x % 3 == 1) ? side(HEIGHT - 5, " > PLAYER", "") : side(HEIGHT - 5, "   PLAYER", "");
    (*x % 3 == 2) ? side(HEIGHT - 4, " > ENEMY", "") : side(HEIGHT - 4, "   ENEMY", "");
}

void game_action_draw(void* value_ptr, Game* game_ptr) {
    int* x = (int*)value_ptr;
    line(HEIGHT - 10);
    (*x % 5 == 0) ? side(HEIGHT - 8, " > ZAP", "") : side(HEIGHT - 6, "   ZAP", "");
    (*x % 5 == 1) ? side(HEIGHT - 7, " > OVERCHARGE", "") : side(HEIGHT - 5, "   OVERCHARGEs", "");
    (*x % 5 == 2) ? side(HEIGHT - 6, " > METEOR SHOWER", "") : side(HEIGHT - 4, "   METEOR SHOWER", "");
    (*x % 5 == 3) ? side(HEIGHT - 5, " > HEAL", "") : side(HEIGHT - 4, "   HEAL", "");
    (*x % 5 == 4) ? side(HEIGHT - 4, " > REST", "") : side(HEIGHT - 4, "   REST", "");
}

void game_msg_draw(void* value_ptr, Game* game_ptr) {
    char* msg = (char*)value_ptr;
    middle(12, msg);
    line(HEIGHT - 10);
    middle(HEIGHT - 8, "< Press Space >");
}

void game_choice_draw(void* value_ptr, Game* game_ptr) {
    int* x = (int*)value_ptr;
    switch (*x % 3) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
    }
    line(HEIGHT - 8);
    (*x % 3 == 0) ? side(HEIGHT - 6, " > GAME", "") : side(HEIGHT - 6, "   GAME", "");
    (*x % 3 == 1) ? side(HEIGHT - 5, " > PLAYER", "") : side(HEIGHT - 5, "   PLAYER", "");
    (*x % 3 == 2) ? side(HEIGHT - 4, " > ENEMY", "") : side(HEIGHT - 4, "   ENEMY", "");
}

// MENUS
// lehetne x % option_count - 1 a visszatérési érték és elég lenne az x hez hozzáadni és kivonni 1-et
// de igy nem lehet az int méretén túl menni

int main_menu() {
    int x = 0;
    int option_count = 3;
    char key;
    while (true) {
        menu_wrapper(main_menu_draw, &x);
        key = getch();
        switch (key) {
        case 'w':
            x = (x > 0) ? (x - 1) : option_count - 1;
            break;
        case 's':
            x = (x < option_count - 1) ? (x + 1) : 0;
            break;
        case '\n':
            return x;
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
        case 'w':
            x = (x > 0) ? (x - 1) : option_count - 1;
            break;
        case 's':
            x = (x < option_count - 1) ? (x + 1) : 0;
            break;
        case '\n':
            return x;
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
        case 'w':
            x = (x > 0) ? (x - 1) : option_count - 1;
            break;
        case 's':
            x = (x < option_count - 1) ? (x + 1) : 0;
            break;
        case '\n':
            switch (x) {
                case 0: return easy_diff_mult;
                case 1: return normal_diff_mult;
                case 2: return hard_diff_mult;
            }
        }
    }
}

void debug(Game* game_ptr) {
    int x = 0;
    int option_count = 3;
    char key;
    bool running = true;
    while (running) {
        game_wrapper(debug_draw, &x, game_ptr);
        key = getch();
        switch (key) {
        case 'w':
            x = (x > 0) ? (x - 1) : option_count - 1;
            break;
        case 's':
            x = (x < option_count - 1) ? (x + 1) : 0;
            break;
        case '\n':
            running = false;
            break;
        }
    }
    
}

int game_action(Game* game_ptr) {
    int x = 0;
    int option_count = 5;
    char key;
    while (true) {
        game_wrapper(game_action_draw, &x, game_ptr);
        key = getch();
        switch (key) {
        case 'w':
            x = (x > 0) ? (x - 1) : option_count - 1;
            break;
        case 's':
            x = (x < option_count - 1) ? (x + 1) : 0;
            break;
        case '\n':
            return x;
        }
    }
    
}

int game_msg(char* msg, Game* game_ptr) {
    char key;
    while (true) {
        game_wrapper(game_msg_draw, msg, game_ptr);
        key = getch();
        if (key == ' ') break;
    }
    
}