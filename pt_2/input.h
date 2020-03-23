#ifndef input_h
#define input_h

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_CAPACITY 10

char* get_next_word(FILE* file);

void delete_word(char* word);

#endif /* input_h */