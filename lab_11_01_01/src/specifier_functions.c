#include "../inc/specifier_functions.h"
#include "../inc/sizes.h"
#include <stdio.h>

void string_specifier(char *dst, char *src, size_t max_length, int *cur_length)
{
    if (src)
        for (int i = 0; src[i] != '\0'; i++)
        {
            write_symbol(dst, src[i], max_length, cur_length);
        }
}

void write_symbol(char *dst, char symbol, size_t max_length, int *cur_length)
{
    if (*cur_length < (int)max_length - 1)
    {
        if (dst)
            dst[*cur_length] = symbol;
    }

    (*cur_length)++;
}

int digit_to_string(char *char_digit, int max_len, int digit)
{
    int start_position = max_len;

    if (char_digit)
    {
        while (digit > 0)
        {
            start_position--;
            char_digit[start_position] = '0' + digit % 10;
            digit /= 10;
        }
    }

    return start_position;
}

void digit_specifier(char *dst, int digit, size_t max_length, int *cur_length)
{
    if (digit == 0)
        write_symbol(dst, '0', max_length, cur_length);
    else if (digit < 0)
    {
        write_symbol(dst, '-', max_length, cur_length);
        digit *= -1;
    }

    if (digit > 0)
    {
        char string_number[INT_LEN + 1];
        string_number[INT_LEN] = '\0';

        int start_position = digit_to_string(string_number, INT_LEN, digit);

        string_specifier(dst, string_number + start_position, max_length, cur_length);
    }
}

int digit_to_hex_string(char *char_digit, int max_len, int digit)
{
    int start_position = max_len;

    if (char_digit)
    {
        int cur_numeral = 0;
        while (digit > 0)
        {
            start_position--;
            cur_numeral = digit % 16;

            if (cur_numeral < 10)
                char_digit[start_position] = '0' + cur_numeral;
            else
                char_digit[start_position] = 'a' + (cur_numeral - 10);

            digit /= 16;
        }
    }

    return start_position;
}

void hex_specifier(char *dst, unsigned int digit, size_t max_length, int *cur_length)
{
    if (digit == 0)
        write_symbol(dst, '0', max_length, cur_length);
    else
    {
        char string_number[INT_LEN + 1];
        string_number[INT_LEN] = '\0';

        int start_position = digit_to_hex_string(string_number, INT_LEN, digit);

        string_specifier(dst, string_number + start_position, max_length, cur_length);
    }
}
