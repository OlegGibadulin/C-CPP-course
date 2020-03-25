#ifndef trie_h
#define trie_h

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#include "file_top.h"

#define ALPHABET_SIZE 26

typedef struct TrieNode TrieNode;
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    int* file_word_count;
    bool is_end_of_word;
};

int increase_word_count(TrieNode* node, const int file_index);

int insert_into_trie(TrieNode** root, const char* word,
                 const int file_count, const int file_index);

TrieNode* search_in_trie(TrieNode* root, const char* word);

void delete_trie(TrieNode* root);

void form_top_words(FileTop** top_words, char* word, const TrieNode* root,
                    const int letter_index, const int* files_words_count,
                    const int files_count);

#endif /* trie_h */
