#include <stdarg.h>
#include "../inc/my_snprintf.h"
#include "../inc/specifier_functions.h"

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    int return_len = 0;

    if (format == NULL)
        return_len = -1;
    else
    {
        va_list args;
        va_start(args, format);

        for (int i = 0; format[i] != '\0' && return_len != -1; i++)
        {
            if (format[i] == '%')
            {
                if (format[i + 1] == 's')
                {
                    i++;
                    char *arg_string = va_arg(args, char *);

                    string_specifier(s, arg_string, n, &return_len);
                }
                else if (format[i + 1] == 'c')
                {
                    i++;
                    char arg_char = (char)va_arg(args, int);

                    write_symbol(s, arg_char, n, &return_len);
                }
                else if (format[i + 1] == 'd')
                {
                    i++;
                    int digit = (int)va_arg(args, int);

                    digit_specifier(s, digit, n, &return_len);
                }
                else if (format[i + 1] == 'h' && format[i + 2] == 'd')
                {
                    i += 2;
                    short int short_digit = (int)va_arg(args, int);

                    digit_specifier(s, (int)short_digit, n, &return_len);
                }
                else if (format[i + 1] == 'x')
                {
                    i++;
                    unsigned int hex_digit = va_arg(args, unsigned int);

                    hex_specifier(s, hex_digit, n, &return_len);
                }
                else if (format[i + 1] == 'h' && format[i + 2] == 'x')
                {
                    i += 2;
                    unsigned short int short_hex_digit = (unsigned short int)va_arg(args, unsigned int);

                    hex_specifier(s, (unsigned int)short_hex_digit, n, &return_len);
                }
                else if (format[i + 1] == '%')
                {
                    i++;
                    write_symbol(s, '%', n, &return_len);
                }
                else
                    return_len = -1;
            }
            else
            {
                write_symbol(s, format[i], n, &return_len);
            }
        }

        if (s && return_len >= (int) n)
        {
            s[n - 1] = '\0';
        }
        else if (s)
            s[return_len] = '\0';

        va_end(args);
    }

    return return_len;
}
