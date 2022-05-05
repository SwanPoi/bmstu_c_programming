#include <stdio.h>
#include <string.h>

#define SIZE_OF_STR 256
#define SIZE_OF_WORD 16

#define ERR_OK 0
#define ERR_INPUT 1
#define ERR_NO_WORDS 2
#define ERR_NO_UNIQ_WORDS 3

size_t get_words(char *str, char *split, char (*words)[SIZE_OF_WORD + 1]);
size_t get_uniq_words(char (*src_words)[SIZE_OF_WORD + 1], size_t length, char unique_words[SIZE_OF_STR + 1]);
void only_uniq_symbols(char full_word[SIZE_OF_WORD + 1], char new_word[SIZE_OF_WORD + 1]);

int main(void)
{
    int rc = ERR_OK;
    char string[SIZE_OF_STR + 1];
    char words[SIZE_OF_STR / 2][SIZE_OF_WORD + 1];
    char uniq_words[SIZE_OF_STR + 1];

    printf("Input first string: ");
    char *check = fgets(string, SIZE_OF_STR, stdin);
    
    if (check)
    {
        size_t count_words = get_words(string, " ,.;:-!?\n\t", words);

        if (count_words)
        {
            size_t uniq_words_count = get_uniq_words(words, count_words, uniq_words);

            if (uniq_words_count)
                printf("Result: %s\n", uniq_words);
            else
                rc = ERR_NO_UNIQ_WORDS;
        }
        else
            rc = ERR_NO_WORDS;
    }
    else
        rc = ERR_INPUT;
    
    return rc;
}

size_t get_words(char *str, char *split, char (*words)[SIZE_OF_WORD + 1])
{
    size_t count_words = 0;

    char *word = strtok(str, split);

    while (word)
    {
        strcpy(*(words + count_words), word);

        word = strtok(NULL, split);
        count_words++;
    }

    return count_words;
}

size_t get_uniq_words(char (*src_words)[SIZE_OF_WORD + 1], size_t length, char unique_words[SIZE_OF_STR + 1])
{
    size_t uniq_count = 0;
    for (size_t i = length - 1; i > 0; i--)
        if (strcmp(*(src_words + i - 1), *(src_words + length - 1)))
        {
            char not_full_word[SIZE_OF_WORD + 1] = { "\n" };
            only_uniq_symbols(*(src_words + i - 1), not_full_word);
            if (i == length - 1)
                strcpy(unique_words, not_full_word);
            else
                strcat(unique_words, not_full_word);

            if (i > 1)
                strcat(unique_words, " ");

            uniq_count++;
        }
    return uniq_count;
}

void only_uniq_symbols(char full_word[SIZE_OF_WORD + 1], char new_word[SIZE_OF_WORD + 1])
{
    size_t full_index = 0;
    size_t uniq_index = 0;
    while (*(full_word + full_index))
    {
        if (!uniq_index || !strchr(new_word, *(full_word + full_index)))
        {
            *(new_word + uniq_index) = *(full_word + full_index);
            uniq_index++;
        }
        full_index++;
    }
    *(new_word + uniq_index) = '\0';
}
