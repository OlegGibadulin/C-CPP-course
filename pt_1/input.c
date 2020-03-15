#include "input.h"

char* input_string(FILE* file) {
    if (!file) {
        return NULL;
    }

    int capacity = BUFFER_CAPACITY;
    char* buffer = (char*) malloc(sizeof(char) * capacity);
    if (!buffer) {
        return NULL;
    }

    int size = 0;
    int ch = 0;
    while (((ch = fgetc(file)) != EOF) && ch != '\n') {
        buffer[size++] = ch;
        if (size == capacity) {
            capacity *= 2;
            char* tmp = (char*) realloc(buffer, sizeof(char) * capacity);
            if (!tmp) {
                free(buffer);
                return NULL;
            }
            free(buffer);
            buffer = tmp;
        }
    }
    buffer[size++] = '\0';

    char* tmp = (char*) realloc(buffer, sizeof(char) * size);
    if (!tmp) {
        free(buffer);
        return NULL;
    }
    buffer = tmp;

    return buffer;
}


int input_int_number(FILE* file, int* num) {
    if (!file || !num) {
        return 1;
    }

    char* str_num = input_string(file);
    if (!str_num) {
        return 1;
    }
    if (*str_num == '\0') {
        free(str_num);
        return 1;
    }

    char* end = NULL;
    *num = strtol(str_num, &end, 10);

    if (*end != '\0') {
        free(str_num);
        return 1;
    }
    free(str_num);

    return 0;
}

int input_hours_and_minutes(FILE* file, struct tm* time) {
    if (!file || !time) {
        return 1;
    }

    char* str_time = input_string(file);
    if (!str_time) {
        return 1;
    }
    if (*str_time == '\0') {
        free(str_time);
        return 1;
    }

    char* separator = NULL;
    int hour = strtol(str_time, &separator, 10);

    if (str_time == separator || *separator != TIME_SEPARATOR || hour < 0) {
        free(str_time);
        return 1;
    }

    char* end = NULL;
    ++separator;
    int min = strtol(separator, &end, 10);

    if (separator == end || *end != '\0' || min < 0 || min > 59) {
        free(str_time);
        return 1;
    }
    free(str_time);

    time->tm_hour = hour;
    time->tm_min = min;

    return 0;
}

