#include "trie.h"

int get_index_from_letter(const char letter) {
    return (int)tolower(letter) - (int)'a';
}

int get_letter_from_index(const int index) {
    return index + (int)'a';
}

int increase_word_count(TrieNode *node, const int file_index) {
    if (!node) {
        return 1;
    }

    node->file_word_count[file_index] += 1;

    return 0;
}

TrieNode *create_trie_node() {
    TrieNode *new_node = (TrieNode *)malloc(sizeof(TrieNode));

    if (new_node) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            new_node->children[i] = NULL;
        }
        new_node->file_word_count = NULL;
        new_node->is_end_of_word = false;
    }

    return new_node;
}

int insert_into_trie(TrieNode **root, const char *word,
                     const int file_count, const int file_index) {
    if (!word) {
        return 1;
    }

    if (!*root) {
        *root = create_trie_node();
    }

    int word_length = strlen(word);
    TrieNode *cur_node = *root;

    for (int i = 0; i < word_length; ++i) {
        int letter_index = get_index_from_letter(word[i]);

        if (!cur_node->children[letter_index]) {
            if (!(cur_node->children[letter_index] = create_trie_node())) {
                return 1;
            }
        }
        cur_node = cur_node->children[letter_index];
    }
    cur_node->is_end_of_word = true;
    cur_node->file_word_count = (int *)calloc(file_count, sizeof(int));

    return increase_word_count(cur_node, file_index);
}

TrieNode *search_in_trie(TrieNode *root, const char *word) {
    if (!root || !word) {
        return NULL;
    }

    TrieNode *cur_node = root;
    int word_index = 0;
    const int word_length = strlen(word);

    while (cur_node && word_index < word_length) {
        int letter_index = get_index_from_letter(word[word_index++]);
        cur_node = cur_node->children[letter_index];
    }
    bool searched = (cur_node && cur_node->is_end_of_word && word_index == word_length);

    return searched ? cur_node : NULL;
}

void delete_trie(TrieNode *root) {
    if (!root) {
        return;
    }

    if (root->is_end_of_word) {
        free(root->file_word_count);
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i]) {
            delete_trie(root->children[i]);
        }
    }

    free(root);
}

double calc_idf_metrics(const int *word_count, const int files_count) {
    if (!word_count) {
        return -1;
    }

    int files_contains_word_count = 0;

    for (int i = 0; i < files_count; ++i) {
        if (word_count[i] != 0) {
            ++files_contains_word_count;
        }
    }

    return log((double)files_count / (double)files_contains_word_count);
}

double calc_tf_metrics(const int word_count, const int files_words_count) {
    return (double)word_count / (double)files_words_count;
}

double calc_tf_idf_metrics(const double tf_metrics, const double idf_metrics) {
    return tf_metrics * idf_metrics;
}

void form_top_words(FileTop **top_words, char *word, const TrieNode *root,
                    const int letter_index, const int *files_words_count,
                    const int files_count) {
    if (!root && !word) {
        return;
    }

    if (root->is_end_of_word) {
        word[letter_index] = '\0';

        double idf_metrics = calc_idf_metrics(root->file_word_count, files_count);

        for (int file_i = 0; file_i < files_count; ++file_i) {
            if (root->file_word_count[file_i] == 0) {
                continue;
            }
            double tf_metrics = calc_tf_metrics(root->file_word_count[file_i],
                                                files_words_count[file_i]);
            double tf_idf_metrics = calc_tf_idf_metrics(tf_metrics, idf_metrics);

            update_file_top(top_words[file_i], word, letter_index, tf_idf_metrics);
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i]) {
            word[letter_index] = get_letter_from_index(i);
            form_top_words(top_words, word, root->children[i], letter_index + 1,
                           files_words_count, files_count);
        }
    }
}
