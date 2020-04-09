#ifndef file_top_h
#define file_top_h

#include <stdlib.h>
#include <string.h>

typedef struct FileTop {
    double *words_metrics;
    char **words;
    int words_count;
    char *file_name;
} FileTop;

FileTop **create_files_top(const int files_count, const int words_count);

void delete_files_top(FileTop **files_top, const int files_count);

void update_file_top(FileTop *file_top, const char *word,
                     const int word_size, const double word_metrics);

#endif /* file_top_h */
