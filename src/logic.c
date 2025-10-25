#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "logic.h"

// returns the bigger
int max(int a, int b) {
    return (a > b) ? a : b;
}

// returns the smaller
int min(int a, int b) {
    return (a < b) ? a : b;
}

// returns a random int in the range including both ends
int randint(int start, int end) {
    srand(time(NULL));
    return (rand()%(end - start + 1)) + start;
}

// return a formatted str with the values
char* format_string(const char* format, ...) {
    static char buffer[50];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    return buffer;
};