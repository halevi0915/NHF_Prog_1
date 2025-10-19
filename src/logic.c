#include <stdlib.h>
#include <stdio.h>

#include "logic.h"

// max
int max(int a, int b) {
    return (a > b) ? a : b;
}

// min
int min(int a, int b) {
    return (a < b) ? a : b;
}

// returns a random int in the range  0 - count
int random_element(int count) {
    return (rand()%count);
}

// return a formatted str with an int
char* format_str_int(char msg[], int value) {
    static char buffer[50];
    sprintf(buffer, msg, value);
    return buffer;
}

// return a formatted str with a str
char* format_str_str(char msg[], char value[]) {
    static char buffer[50];
    sprintf(buffer, msg, value);
    return buffer;
}