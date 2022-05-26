#include <stdio.h>
#include <string.h>

#define SIZE_OF_STR 256
#define SIZE_OF_WORD 16
#define IN_LIST 1
#define NOT_IN_LIST 0

#define ERR_OK 0
#define ERR_INPUT 1
#define ERR_NO_WORDS 2
#define ERR_NO_UNIQ_WORDS 3

size_t get_words(char *str, char *split, char **words);
int is_symbol_in_list(char symbol, char *split);
int search_in_array(char *element, char **words, size_t length);
int search_in_self(size_t index, char **words, size_t length);
int form_array_of_uniq_words(char **words_in_first, size_t first_length, char **words_in_second, size_t second_length, char **uniq_words);
void substr_cpy(char *src_start, char *src_end, char *dest);
void print_array(char **words, size_t length);
void transform(char **matrix, char *src, size_t rows, size_t columns);


int main(void)
{
    int rc = ERR_OK;
    char first_string[SIZE_OF_STR + 1], second_string[SIZE_OF_STR + 1];
    char matr_words_in_first[SIZE_OF_STR / 2][SIZE_OF_WORD + 1];
    char matr_words_in_second[SIZE_OF_STR / 2][SIZE_OF_WORD + 1];
    char matr_uniq_words[SIZE_OF_STR + 1][SIZE_OF_WORD + 1];
    
    char *words_in_first[SIZE_OF_STR / 2];
    char *words_in_second[SIZE_OF_STR / 2];
    char *uniq_words[SIZE_OF_STR + 1];

    printf("Input first string: ");
    char *first_check = fgets(first_string, SIZE_OF_STR, stdin);
    
    if (first_check)
    {
        printf("Input second string: ");
        char *second_check = fgets(second_string, SIZE_OF_STR, stdin);
        
        if (second_check)
        {
            transform(words_in_first, *matr_words_in_first, SIZE_OF_STR / 2, SIZE_OF_WORD + 1);
            transform(words_in_second, *matr_words_in_second, SIZE_OF_STR / 2, SIZE_OF_WORD + 1);
            transform(uniq_words, *matr_uniq_words, SIZE_OF_STR + 1, SIZE_OF_WORD + 1);
            
            size_t count_words_in_first = get_words(first_string, " ,.;:-!?\n\t", words_in_first);
            size_t count_words_in_second = get_words(second_string, " ,.;:-!?\n\t", words_in_second);

            if (count_words_in_first && count_words_in_second)
            {
                int count_uniq = form_array_of_uniq_words(words_in_first, count_words_in_first, words_in_second, count_words_in_second, uniq_words);

                if (count_uniq)
                    print_array(uniq_words, count_uniq);
                else
                    rc = ERR_NO_UNIQ_WORDS;
            }
            else
                rc = ERR_NO_WORDS;
        }
        else
            rc = ERR_INPUT;
    }
    else
        rc = ERR_INPUT;
    
    return rc;
}

size_t get_words(char *str, char *split, char **words)
{
    size_t index = 0, count_words = 0, start = 0, end = 0;

    while (*(str + index))
    {
        if (is_symbol_in_list(*(str + index), split) == NOT_IN_LIST)
            end++;
        else
        {
            if (start != end)
            {
                substr_cpy(str + start, str + end, words[count_words]);
                count_words++;
            }
            start = ++end;
        }

        index++;
    }


    return count_words;
}

int is_symbol_in_list(char symbol, char *split)
{
    size_t index = 0;
    int symbol_in = NOT_IN_LIST;

    while (*(split + index) && symbol_in == NOT_IN_LIST)
    {
        if (*(split + index) == symbol)
            symbol_in = IN_LIST;
        index++;
    }

    return symbol_in;
}

void substr_cpy(char *src_start, char *src_end, char *dest)
{
    size_t index = 0;
    for (; src_start + index != src_end; index++)
        *(dest + index) = *(src_start + index);

    *(dest + index) = '\0';
}

int search_in_array(char *element, char **words, size_t length)
{
    int is_in = NOT_IN_LIST;
    for (size_t i = 0; i < length && is_in == NOT_IN_LIST; i++)
        if (!strcmp(element, words[i]))
            is_in = IN_LIST;

    return is_in;
}

int search_in_self(size_t index, char **words, size_t length)
{
    int is_in = NOT_IN_LIST;
    for (size_t i = 0; i < length && is_in == NOT_IN_LIST; i++)
        if (i != index && !strcmp(words[index], words[i]))
            is_in = IN_LIST;
            
    return is_in;
}

void print_array(char **words, size_t length)
{
    printf("Result: ");
    for (size_t i = 0; i < length; i++)
        if (i < length - 1)
            printf("%s ", words[i]);
        else
            printf("%s", words[i]);
    printf("\n");
}

int form_array_of_uniq_words(char **words_in_first, size_t first_length, char **words_in_second, size_t second_length, char **uniq_words)
{
    int count_uniq = 0;

    for (size_t i = 0; i < first_length; i++)
        if (search_in_array(words_in_first[i], words_in_second, second_length) == NOT_IN_LIST &&
            search_in_self(i, words_in_first, first_length) == NOT_IN_LIST)
        {
            strcpy(uniq_words[count_uniq], words_in_first[i]);
            count_uniq++;
        }

    for (size_t i = 0; i < second_length; i++)
        if (search_in_array(words_in_second[i], words_in_first, first_length) == NOT_IN_LIST &&
            search_in_self(i, words_in_second, second_length) == NOT_IN_LIST)
        {
            strcpy(uniq_words[count_uniq], words_in_second[i]);
            count_uniq++;
        }

    return count_uniq;
} 

void transform(char **matrix, char *src, size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
        matrix[i] = src + i * columns;
}
