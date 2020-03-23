#include "metrics.h"

#include <stdio.h>

TrieNode* form_words_trie(int* max_word_length, int** files_words_count, const int files_count) {
    if (!max_word_length || !*files_words_count) {
        return NULL;
    }

    TrieNode* root = NULL;

    for (int file_i = 0; file_i < files_count; ++file_i) {
        char* word = (char*) malloc(20);
        if (file_i == 0) {
            strcpy(word, "askflksa\0");
        } else {
            strcpy(word, "skfjlkassa\0");
        }

        int word_length = strlen(word);
        if (word_length) {
            *max_word_length = word_length;
        }

        TrieNode* searched_node = search_in_trie(root, word);
        if (!searched_node) {
            if (insert_into_trie(&root, word, files_count, file_i) != 0) {
                return NULL;
            }
        } else {
            if (increase_word_count(searched_node, file_i) != 0) {
                return NULL;
            }
        }

        ++(*files_words_count)[file_i];
    }

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

    if (!(root = form_words_trie(&max_word_length, &files_words_count, files_count))) {
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
            printf("File #%d\n", i);

            for (int j = 0; j < words_count; ++j) {
                printf("%s\n", files_top[i]->words[j]);
            }
            printf("\n");
        }
    }
}
