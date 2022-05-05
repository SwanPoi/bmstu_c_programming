#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE_OF_STR 256
#define YES 1
#define NO 0
#define NO_CODE -1

#define ERR_OK 0
#define ERR_INPUT 1

int check_begin_tabulation(char *string, size_t length);
int check_end_tabulation(char *string, size_t length);
int check_telephone(char *string, int begin, int end);
int check_if_only_digits(char *begin, char *end);
int check_operator_code(char *begin_of_code, char *end_of_code);
int check_after_operator_code(char *begin, char *end);

int main(void)
{
    int rc = ERR_OK;
    int is_valid = NO;
    char string[SIZE_OF_STR + 1];

    char *check = fgets(string, SIZE_OF_STR + 1, stdin);

    if (check && !(strlen(string) == SIZE_OF_STR && *(string + SIZE_OF_STR + 1) != '\0'))
    {
        size_t length_of_string = strlen(string);
        int begin = check_begin_tabulation(string, length_of_string);
        int end = check_end_tabulation(string, length_of_string);

        if ((size_t) begin != length_of_string)
            is_valid = check_telephone(string, begin, end);

        if (is_valid == YES)
            printf("YES\n");
        else
            printf("NO\n");
    }
    else
        rc = ERR_INPUT;

    return rc;
}

int check_begin_tabulation(char *string, size_t length)
{
    size_t begin = 0;

    while (begin < length && isspace(*(string + begin)))
        begin++;

    return begin;
}

int check_end_tabulation(char *string, size_t length)
{
    int end = (int) length - 1;

    while (end >= 0 && isspace(*(string + end)))
        end--;

    return end;
}

int check_telephone(char *string, int begin, int end)
{
    int is_valid = NO;
    int valid_country_code = NO_CODE;
    int valid_operator_code = NO;
    int valid_else = NO;

    char *begin_of_operator_code = strchr(string, '(');
    char *end_of_operator_code = strchr(string, ')');

    if (begin_of_operator_code < end_of_operator_code)
    {
        if (*(string + begin) == '+')
        {
            valid_country_code = check_if_only_digits(string + begin + 1, begin_of_operator_code);
        }
        else if (*(string + begin) != '(')
            valid_country_code = NO;

        valid_operator_code = check_operator_code(begin_of_operator_code, end_of_operator_code);
        valid_else = check_after_operator_code(end_of_operator_code + 1, string + end);
    }

    if (valid_country_code != NO && valid_operator_code != NO && valid_else != NO)
        is_valid = YES;

    return is_valid;
}

int check_if_only_digits(char *begin, char *end)
{
    int is_valid = YES;
    if (begin == end)
        is_valid = NO;

    for (char *symbol = begin; symbol < end && is_valid == YES; symbol++)
        if (!isdigit(*symbol))
            is_valid = NO;

    return is_valid;
}

int check_operator_code(char *begin_of_code, char *end_of_code)
{
    int is_valid = YES;
    if ((end_of_code - begin_of_code) == 4)
    {
        is_valid = check_if_only_digits(begin_of_code + 1, end_of_code);
    }
    else
        is_valid = NO;

    return is_valid;
}

int check_after_operator_code(char *begin, char *end)
{
    int is_valid = NO;

    if (*begin == '-' && *(begin + 4) == '-' && *(begin + 7) == '-' && (begin + 9) == end)
        is_valid = check_if_only_digits(begin + 1, begin + 4)
                   & check_if_only_digits(begin + 5, begin + 7)
                   & check_if_only_digits(begin + 8, begin + 10);

    return is_valid;
}
