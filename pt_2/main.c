/*
 В вашем распоряжении директория с 500 текстовыми файлами, каждый из которых
 занимает 1 МБ места на диске. Необходимо реализовать последовательную и
 параллельную программу с использованием нескольких процессов получения
 tf-idf-метрики для каждой пары (слово, документ) и вывода топ-5 слов для
 каждого документа.
 */

#include <stdio.h>
#include <time.h>
#include <stddef.h>

#include "metrics.h"

int main() {
    const char* in_dir = "../test";
    const int files_count = 6;
    const int top_words_count = 5;

    time_t start,end;
    start = time (NULL);

    FileTop** files_top = NULL;
    if (!(files_top = create_files_top(files_count, top_words_count))) {
        return 1;
    }

    if (get_top_words_by_tf_idf(files_top, in_dir, files_count,
                                top_words_count) != 0) {
        delete_files_top(files_top, files_count);
        return 1;
    }
    display_files_top(files_top, files_count, top_words_count);

    delete_files_top(files_top, files_count);

    end = time (NULL);
    printf("Required time: %f milliseconds\n", difftime(end, start) / CLOCKS_PER_SEC);

    return 0;
}
