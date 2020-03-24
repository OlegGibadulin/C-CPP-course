#ifndef metrics_h
#define metrics_h

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include "trie.h"
#include "input.h"

int get_top_words_by_tf_idf(FileTop** files_top, const char* dir,
								const int files_count, const int words_count);

void display_files_top(FileTop** files_top, const int files_count, const int words_count);

#endif /* metrics_h */