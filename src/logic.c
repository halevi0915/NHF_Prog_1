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
    srand(time(NULL));
    return (rand()%(end - start + 1)) + start;
}

// return a formatted str with the values
char* format_string(const char* format, ...) {
    va_list args;
    va_start(args, format);

    int len = vsnprintf(NULL, 0, format, args);
    va_end(args); // cleans up in case there is an exit

    if (len < 0) {printf("format error"); exit(1);} // format error

    char* buffer = malloc(len + 1);
    ++malloc_counter;
    if (buffer == NULL) {printf("alloc error"); exit(1);};  // alloc error

    va_start(args, format);
    vsnprintf(buffer, len + 1, format, args);
    va_end(args);

    return buffer;
}