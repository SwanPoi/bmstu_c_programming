#ifndef __SPECIFIER_H__
#define __SPECIFIER_H__

#include <stddef.h>

void write_symbol(char *dst, char symbol, size_t max_length, int *cur_length);
void string_specifier(char *dst, char *src, size_t max_length, int *cur_length);
int digit_to_string(char *char_digit, int max_len, int digit);
void digit_specifier(char *dst, int digit, size_t max_length, int *cur_length);
void hex_specifier(char *dst, unsigned int digit, size_t max_length, int *cur_length);
int digit_to_hex_string(char *char_digit, int max_len, int digit);

#endif // __SPECIFIER_H__