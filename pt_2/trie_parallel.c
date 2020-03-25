#include <pthread.h>
#include <sys/sysinfo.h>

#include "trie.h"

typedef struct Args {
    FileTop** top_words;
    char* word;
    int* file_word_count;
    int letter_index;
    double idf_metrics;
    const int* files_words_count;
} Args;

typedef struct ThreadArgs {
    Args* args;
    int from_index;
    int to_index;
} ThreadArgs;

int get_index_from_letter(const char letter) {
    return (int) tolower(letter) - (int) 'a';
}

int get_letter_from_index(const int index) {
    return index + (int) 'a';
}

int increase_word_count(TrieNode* node, const int file_index) {
    if (!node) {
        return 1;
    }

    node->file_word_count[file_index] += 1;

    return 0;
}

TrieNode* create_trie_node() {
    TrieNode* new_node = (TrieNode*) malloc (sizeof(TrieNode));

    if (new_node) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            new_node->children[i] = NULL;
        }
        new_node->file_word_count = NULL;
        new_node->is_end_of_word = false;
    }

    return new_node;
}

int insert_into_trie(TrieNode** root, const char* word,
                 const int file_count, const int file_index) {
    if (!word) {
        return 1;
    }

    if (!*root) {
        *root = create_trie_node();
    }

    int word_length = strlen(word);
    TrieNode* cur_node = *root;

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
    cur_node->file_word_count = (int*) calloc(file_count, sizeof(int));

    return increase_word_count(cur_node, file_index);
}

TrieNode* search_in_trie(TrieNode* root, const char* word) {
    if (!root || !word) {
        return NULL;
    }

    TrieNode* cur_node = root;
    int word_index = 0;
    const int word_length = strlen(word);

    while (cur_node && word_index < word_length) {
        int letter_index = get_index_from_letter(word[word_index++]);
        cur_node = cur_node->children[letter_index];
    }
    bool searched = (cur_node && cur_node->is_end_of_word && word_index == word_length);

    return searched ? cur_node : NULL;
}

void delete_trie(TrieNode* root) {
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

double calc_idf_metrics(const int* word_count, const int files_count) {
    int files_contains_word_count = 0;

    for (int i = 0; i < files_count; ++i) {
        if (word_count[i] != 0) {
            ++files_contains_word_count;
        }
    }

    return log((double) files_count / (double) files_contains_word_count);
}

double calc_tf_metrics(const int word_count, const int files_words_count) {
    return (double) word_count / (double) files_words_count;
}

double calc_tf_idf_metrics(const double tf_metrics, const double idf_metrics) {
    return tf_metrics * idf_metrics;
}

void* form_top(void* arg) {
    if (!arg) {
        pthread_exit(0);
    }
    ThreadArgs* th_args = (ThreadArgs*) arg;
    if (!th_args) {
        pthread_exit(0);
    }
    Args* args = (Args*) th_args->args;
    if (!args) {
        pthread_exit(0);
    }
    int from_index = (int) th_args->from_index;
    int to_index = (int) th_args->to_index;

    for (int file_i = from_index; file_i < to_index; ++file_i) {
        if (args->file_word_count[file_i] == 0) {
            continue;
        }
        double tf_metrics = calc_tf_metrics(args->file_word_count[file_i],
                                            args->files_words_count[file_i]);
        double tf_idf_metrics = calc_tf_idf_metrics(tf_metrics, args->idf_metrics);

        update_file_top(args->top_words[file_i], args->word, args->letter_index, tf_idf_metrics);
    }

    pthread_exit(0);
}

void form_top_words(FileTop** top_words, char* word, const TrieNode* root,
                    const int letter_index, const int* files_words_count,
                    const int files_count) {
    if (!root && !word) {
        return;
    }

    if (root->is_end_of_word) {
        word[letter_index] = '\0';
        double idf_metrics = calc_idf_metrics(root->file_word_count, files_count);

        int proc_count = get_nprocs();
        pthread_t threads[proc_count];
        Args args;
        ThreadArgs threads_args[proc_count];

        args.top_words = top_words;
        args.word = word;
        args.file_word_count = root->file_word_count;
        args.letter_index = letter_index;
        args.files_words_count = files_words_count;
        args.idf_metrics = idf_metrics;

        double threads_row_count = (double) files_count / proc_count;
        if (threads_row_count < 1) {
            threads_row_count = 1;
        }
        for (int i = 0, from = 0, to = 0; to < files_count; ++i) {
            to += threads_row_count;
            if (i == proc_count - 1) {
                to = files_count;
            }
            threads_args[i].args = &args;
            threads_args[i].from_index = from;
            threads_args[i].to_index = to;
            from = to;
        }

        for (int i = 0; i < proc_count; ++i) {
            pthread_create(&threads[i], NULL, form_top, &threads_args[i]);
        }
        for (int i = 0; i < proc_count; ++i) {
            pthread_join(threads[i], NULL);
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
