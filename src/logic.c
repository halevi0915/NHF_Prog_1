#include <stdlib.h>
#include <stdio.h>

#include "logic.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int random_element(int count) {
    return (rand()%count);
}

char* format_str_int(char msg[], int value) {
    static char buffer[50];
    sprintf(buffer, msg, value);
    return buffer;
}

char* format_str_str(char msg[], char value[]) {
    static char buffer[50];
    sprintf(buffer, msg, value);
    return buffer;
}