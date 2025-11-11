#include "debugmalloc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "logic.h"
#include "globals.h"

// returns the bigger
int max(const int a, const int b) {
    return (a > b) ? a : b;
}

// returns the smaller
int min(const int a, const int b) {
    return (a < b) ? a : b;
}

// returns a random int in the range including both ends
int randint(const int start, const int end) {
    return (rand()%(end - start + 1)) + start;
}

// based on a given percentage, it returns ture or false
int calc_chance(const int chance) {
    return (randint(1,100) <= chance);
}

// return a formatted str with the values
char* format_string(const char* format, ...) {
    va_list args;
    va_start(args, format);

    int len = vsnprintf(NULL, 0, format, args);
    va_end(args); // cleans up in case there is an exit

    if (len < 0) {printf("format error"); exit(1);} // format error

    char* buffer = malloc(sizeof(char) * (len + 1));
    ++malloc_counter;
    if (buffer == NULL) {printf("format str alloc error"); exit(1);};  // alloc error

    va_start(args, format);
    vsnprintf(buffer, len + 1, format, args);
    va_end(args);

    return buffer;
}

// return a str with the values in visual form with the message: message 30/100 --> message [###-------]
char* bar_string(const char* text, const int current_value, const int max_value) {
    int text_len = strlen(text);
    int ratio = ((float)current_value / ((float)max_value / 100)) / 10;

    char* buffer = malloc(sizeof(char) * (13 + text_len));
    ++malloc_counter;

    if (buffer == NULL) {printf("bar str alloc error"); exit(1);};  // alloc error

    for (int i = 0; i < text_len; ++i) {buffer[i] = text[i];}
    buffer[text_len + 0] = '[';
    for (int i = 1; i <= 10; ++i) {buffer[text_len + i] = (i <= ratio) ? '#' : '-';}
    buffer[text_len + 11] = ']';
    buffer[text_len + 12] = '\0';

    return buffer;
}