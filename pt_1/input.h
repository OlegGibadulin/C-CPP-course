#ifndef input_h
#define input_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFER_CAPACITY 10
#define TIME_SEPARATOR ':'

char* input_string(FILE* file);
int input_int_number(FILE* file, int* num);
int input_hours_and_minutes(FILE* file, struct tm* time);

#endif /* input_h */
