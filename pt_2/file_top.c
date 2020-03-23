#include "file_top.h"

FileTop** create_files_top(const int files_count, const int words_count) {
    FileTop** files_top = (FileTop**) malloc(sizeof(FileTop*) * files_count);
    
    if (files_top) {
        for (int i = 0; i < files_count; ++i) {
            files_top[i] = (FileTop*)  malloc(sizeof(FileTop));
            if (!files_top[i]) {
                delete_files_top(files_top, i);
                return NULL;
            }

            files_top[i]->words_metrics = (double*) calloc(words_count, sizeof(double));
            if (!files_top[i]->words_metrics) {
                free(files_top[i]);
                delete_files_top(files_top, i);
                return NULL;
            }

            files_top[i]->words = (char**) malloc(sizeof(char*) * words_count);
            if (!files_top[i]->words) {
                free(files_top[i]);
                free(files_top[i]->words_metrics);
                delete_files_top(files_top, i);
                return NULL;
            }

            files_top[i]->words_count = words_count;
        }
    }

    return files_top;
}

void delete_files_top(FileTop** files_top, const int files_count) {
    for (int i = 0; i < files_count; ++i) {
        free(files_top[i]->words_metrics);
        free(files_top[i]->words);
        free(files_top[i]);
    }

    free(files_top);
}

void update_file_top(FileTop* file_top, const char* word,
                     const int word_size, const double word_metrics) {
    if (!file_top || !word) {
        return;
    }

    for (int i = 0; i < file_top->words_count; ++i) {
        if (word_metrics > file_top->words_metrics[i]) {
            file_top->words_metrics[i] = word_metrics;

            char* tmp = (char*) malloc(sizeof(char) * word_size);
            if (tmp) {
                if (file_top->words[i]) {
                    free(file_top->words[i]);
                }
                strcpy(tmp, word);
                file_top->words[i] = tmp;
            }

            return;
        }
    }
}
