#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "logic.h"

// max
int max(int a, int b) {
    return (a > b) ? a : b;
}

// min
int min(int a, int b) {
    return (a < b) ? a : b;
}

// returns a random int in the range including both ends
int randint(int start, int end) {
    srand(time(NULL));
    return (rand()%(end - start + 1)) + start;
}

// return a formatted str with an int
char* format_str_int(char msg[], int value) {
    static char buffer[50];
    sprintf(buffer, msg, value);
    return buffer;
}

// return a formatted str with 2 int
char* format_str_2int(char msg[], int value1, int value2) {
    static char buffer[50];
    sprintf(buffer, msg, value1, value2);
    return buffer;
}

// return a formatted str with a float
char* format_str_float(char msg[], float value) {
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