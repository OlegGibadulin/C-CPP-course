#include <gtest/gtest.h>
#include <stdbool.h>
#include <string.h>

#include "trie.h"

TEST(create_trie_node, pos) {
    TrieNode *node = create_trie_node();
    bool result = (node != NULL);
    delete_trie(node);
    ASSERT_EQ(result, true);
}

TEST(insert_into_trie, neg) {
    const int file_count = 10;
    const int file_index = 0;
    ASSERT_EQ(insert_into_trie(NULL, NULL, file_count, file_index), 1);
}

TEST(insert_into_trie, pos) {
    const int file_count = 10;
    const int file_index = 0;
    TrieNode *root = NULL;
    const char *word = "test";
    bool result = (insert_into_trie(&root, word, file_count, file_index) == 0 && root);
    delete_trie(root);

    ASSERT_EQ(result, true);
}

TEST(increase_word_count, neg) {
    const int file_index = 0;
    ASSERT_EQ(increase_word_count(NULL, file_index), 1);
}

TEST(form_top_words, pos) {
    const int files_count = 1;
    const int file_index = 0;
    TrieNode *root = NULL;
    const char *in_word = "test";
    if (insert_into_trie(&root, in_word, files_count, file_index) != 0 || !root)
    {
        ASSERT_EQ(false, true);
    }

    const int top_words_count = 5;
    FileTop **top_words = NULL;
    if (!(top_words = create_files_top(files_count, top_words_count)))
    {
        ASSERT_EQ(false, true);
    }

    char *word = (char *)malloc(sizeof(char) * strlen(in_word) + 1);
    const int letter_index = 0;
    int *files_words_count = (int *)malloc(sizeof(int));
    files_words_count[0] = 1;
    form_top_words(top_words, word, root, letter_index, files_words_count, files_count);

    bool result = (strcmp(top_words[0]->words[0], in_word) == 0);

    free(word);
    delete_trie(root);
    delete_files_top(top_words, files_count);

    ASSERT_EQ(result, true);
}

TEST(update_file_top, pos) {
    const int files_count = 2;
    const int top_words_count = 5;
    FileTop **files_top = NULL;
    if (!(files_top = create_files_top(files_count, top_words_count)))
    {
        ASSERT_EQ(false, true);
    }
    const char *word = "test";
    int word_size = strlen(word);
    double words_metrics = 1.5;

    update_file_top(files_top[0], word, word_size, words_metrics);
    bool result = (strcmp(files_top[0]->words[0], word) == 0);
    delete_files_top(files_top, files_count);

    ASSERT_EQ(result, true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
