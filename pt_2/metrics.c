#include "metrics.h"

char* get_path(const char* dir_name, const char* file_name) {
    char* path_to_file = (char*) malloc(strlen(dir_name) + strlen(file_name) + 2);
    strcpy(path_to_file, dir_name);
    strcat(path_to_file, "/");
    strcat(path_to_file, file_name);

    return path_to_file;
}

int form_trie(TrieNode** root, FILE* in_file, int* max_word_length,
              int** files_words_count, const int files_count, const int file_i) {
    if (!in_file || !max_word_length || !*files_words_count) {
        return 1;
    }

    char* word = NULL;
    while ((word = get_next_word(in_file))) {
        int word_length = strlen(word);
        if (word_length > *max_word_length) {
            *max_word_length = word_length;
        }

        TrieNode* searched_node = search_in_trie(*root, word);
        if (!searched_node) {
            if (insert_into_trie(root, word, files_count, file_i) != 0) {
                delete_word(word);
                return 1;
            }
        } else {
            if (increase_word_count(searched_node, file_i) != 0) {
                delete_word(word);
                return 1;
            }
        }
        ++(*files_words_count)[file_i];
        delete_word(word);
    }

    return 0;
}

TrieNode* get_trie(FileTop** files_top, int* max_word_length, int** files_words_count,
                          const int files_count, const char* dir_name) {
    if (!*files_top || !max_word_length || !*files_words_count || !dir_name) {
        return NULL;
    }

    TrieNode* root = NULL;
    DIR* dir = opendir(dir_name);
    if (!dir) {
        return NULL;
    }
    struct dirent* entry;

    for (int file_i = 0; file_i < files_count; ++file_i) {
        if (!(entry = readdir(dir))) {
            closedir(dir);
            return NULL;
        }
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            --file_i;
            continue;
        }

        files_top[file_i]->file_name = get_path(dir_name, entry->d_name);
        FILE* in_file = fopen(files_top[file_i]->file_name, "r");
        if (!in_file || form_trie(&root, in_file, max_word_length,
            files_words_count, files_count, file_i) != 0) {
            fclose(in_file);
            closedir(dir);
            return NULL;
        }
        fclose(in_file);
    }
    closedir(dir);

    return root;
}

int get_top_words_by_tf_idf(FileTop** files_top, const char* dir,
                            const int files_count, const int words_count) {
    if (!files_top || !dir) {
        return 1;
    }

    TrieNode* root = NULL;
    int max_word_length = 0;
    int* files_words_count = (int*) calloc(files_count, sizeof(int));
    if (!files_words_count) {
        return 1;
    }

    if (!(root = get_trie(files_top, &max_word_length, &files_words_count, files_count, dir))) {
        delete_trie(root);
        free(files_words_count);
        return 1;
    }

    char word[max_word_length + 1];
    int letter_index = 0;
    form_top_words(files_top, word, root, letter_index, files_words_count, files_count);

    delete_trie(root);
    free(files_words_count);

    return 0;
}

void display_files_top(FileTop** files_top, const int files_count, const int words_count) {
    if (!files_top) {
        return;
    }

    for (int i = 0; i < files_count; ++i) {
        if (files_top[i]) {
            printf("File %s\n", files_top[i]->file_name);

            for (int j = 0; j < words_count; ++j) {
                printf("%s\n", files_top[i]->words[j]);
            }
            printf("\n");
        }
    }
}
