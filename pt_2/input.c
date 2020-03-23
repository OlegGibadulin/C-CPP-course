#include "input.h"

char* get_next_word(FILE* file) {
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
    	if (ch == ' ') {
    		if (size == 0) {
    			continue;
    		} else {
    			break;
    		}
    	}

        buffer[size++] = ch;
        if (size + 1 == capacity) {
            capacity *= 2;
            char* tmp = (char*) realloc(buffer, sizeof(char) * capacity);
            if (!tmp) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
    }

    if (size == 0) {
    	free(buffer);
        return NULL;
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

void delete_word(char* word) {
	if (word) {
		free(word);
	}
}
