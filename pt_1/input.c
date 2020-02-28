#include "input.h"

char* input_string(FILE* file) {
    int capacity = BUFFER_CAPACITY;
    char* buffer = malloc(sizeof(char) * capacity);
    if (!buffer) {
        return NULL;
    }

    int size = 0;
    int ch;
    while (((ch = fgetc(file)) != EOF) && ch != '\n') {
        buffer[size++] = ch;
        if (size == capacity) {
            capacity *= 2;
            char* tmp = realloc(buffer, sizeof(char) * capacity);
            free(buffer);
            if (!tmp) {
                return NULL;
            }
            buffer = tmp;
        }
    }
    buffer[size++] = '\0';

    buffer = realloc(buffer, sizeof(char) * size);
    if (!buffer) {
        return NULL;
    }

    return buffer;
}


int input_int_number(int* num) {
    char* str = input_string(stdin);
    if (!str) {
        return 1;
    }

    char* end;
    *num = strtol(str, &end, 10);

    if (*end != '\0') {
        free(str);
        return 1;
    }
    free(str);

    return 0;
}

