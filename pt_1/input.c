#include "input.h"

char* input_string(FILE* const file) {
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


int input_int_number(FILE* const file, int* num) {
    char* str_num = input_string(file);
    if (!str_num || *str_num == '\0') {
        return 1;
    }

    char* end;
    *num = strtol(str_num, &end, 10);

    if (*end != '\0') {
        free(str_num);
        return 1;
    }
    free(str_num);

    return 0;
}

int input_hours_and_minutes(FILE* const file, struct tm* time) {
    char* str_time = input_string(file);
    if (!str_time || *str_time == '\0') {
        return 1;
    }

    char* separator;
    int hour = strtol(str_time, &separator, 10);

    if (str_time == separator || *separator != TIME_SEPARATOR) {
        free(str_time);
        return 1;
    }

    char* end;
    ++separator;
    int min = strtol(separator, &end, 10);

    if (separator == end || *end != '\0') {
        free(str_time);
        return 1;
    }
    free(str_time);

    time->tm_hour = hour;
    time->tm_min = min;

    return 0;
}

