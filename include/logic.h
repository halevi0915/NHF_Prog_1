#ifndef LOGIC_H
#define LOGIC_H

int max(int a, int b);
int min(int a, int b);
int randint(int start, int end);
char* format_str_int(char msg[], int value);
char* format_str_2int(char msg[], int value1, int value2);
char* format_str_float(char msg[], float value);
char* format_str_str(char msg[], char value[]);

#endif