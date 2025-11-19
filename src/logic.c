#include "debugmalloc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "logic.h"
#include "globals.h"

// returns the bigger int
int max(const int a, const int b) {
    return (a > b) ? a : b;
}

// returns the smaller int
int min(const int a, const int b) {
    return (a < b) ? a : b;
}

// returns a random int in the range including both ends
int randint(const int start, const int end) {
    return (rand()%(end - start + 1)) + start;
}

// based on a given percentage, it returns ture or false
bool calc_chance(const int chance) {
    return (randint(0,100) <= chance);
}

// return a formatted str with the values
char* format_string(const char* format, ...) {
    va_list args; // init args
    va_start(args, format); // start args

    int len = vsnprintf(NULL, 0, format, args); // gets the length
    va_end(args); // cleans up in case there is an exit

    if (len < 0) {perror("format-str format error"); exit(2);} // format error -> retruns 0 for the len

    char* buffer = malloc(sizeof(char) * (len + 1)); // +1 for the \0
    if (buffer == NULL) {perror("format-str alloc error"); exit(1);};  // alloc error

    va_start(args, format); // reinit args
    vsnprintf(buffer, len + 1, format, args); // does the formatting
    va_end(args); // close args

    return buffer;
}

// return a str with the values in visual form with the message: message 30/100 --> message [###-------]
char* bar_string(const char* text, const int current_value, const int max_value) {
    int text_len = strlen(text);
    int ratio = ((float)current_value / ((float)max_value / 100)) / 10; // float division for precision, rounded to 10

    char* buffer = malloc(sizeof(char) * (13 + text_len)); // 12 is the len of [####------] and +1 for \0

    if (buffer == NULL) {perror("bar-str alloc error"); exit(1);};  // alloc error

    // writes the vaules in
    for (int i = 0; i < text_len; ++i) {buffer[i] = text[i];}
    buffer[text_len + 0] = '[';
    for (int i = 1; i <= 10; ++i) {buffer[text_len + i] = (i <= ratio) ? '#' : '-';}
    buffer[text_len + 11] = ']';
    buffer[text_len + 12] = '\0';

    return buffer;
}

void save_game(Game* game_ptr, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) {perror("save_game open error"); exit(3);}

    if (fwrite(game_ptr, sizeof(Game), 1, f) != 1) {perror("save_game write error"); fclose(f); exit(5);}

    Slot* item = game_ptr->player.inventory;
    while (item != NULL) {
        if (fwrite(&item->contents, sizeof(Item), 1, f) != 1) {perror("save_game write error"); fclose(f); exit(5);}
        item = item->next;
    }
    fclose(f);
}

bool load_game(Game* game_ptr, const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) {perror("load_game open error"); exit(3);}

    
    if (fread(game_ptr, sizeof(Game), 1, f) != 1) {perror("load_game read error"); fclose(f); exit(4);}

    game_ptr->player.inventory = NULL;
    for (int i = 0; i < game_ptr->player.item_count; i++) {
        Item item;
        
        if (fread(&item, sizeof(Item), 1, f) != 1) {perror("load_game read error"); fclose(f); exit(4);}

        Slot* new_slot = (Slot*)malloc(sizeof(Slot));
        new_slot->contents = item;
        new_slot->next = NULL;

        Slot* end_finder = game_ptr->player.inventory;
        if (end_finder == NULL) game_ptr->player.inventory = new_slot;
        else {
            while (end_finder->next != NULL) end_finder = end_finder->next;
            end_finder->next = new_slot;
        }
    }
    fclose(f);
    return true;
}

bool save_exists(const char* file_name) {
    FILE* f = fopen(file_name, "rb");
    if (f) {fclose(f); return true;}
    return false;
}
