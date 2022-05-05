#include <stdio.h>
#include <string.h>

size_t my_strspn(const char *s, const char *accept);
size_t my_strcspn(const char *s, const char *reject);
char *my_strpbrk(const char *s, const char *accept);

int main(void)
{
    int failed = 0;

    // Tests for strspn
    char *first_string = "Hello there";
    char *second_string = "Hellw";
    char *full_in = "Hello there Obi Wan Kennobi";
    char *no_in = "May force be with you";

    failed += !(strspn(first_string, second_string) == my_strspn(first_string, second_string));
    failed += !(strspn(first_string, full_in) == my_strspn(first_string, full_in));
    failed += !(strspn(first_string, no_in) == my_strspn(first_string, no_in));


    // Tests for strcspn
    char *third_string = "I like to spin poi and juggle them";
    char *first_symbol = "abcdI";
    char *last_symbol = "1234m56";
    char *random_symbol = "ai";
    char *no_entry = "12345";

    failed += !(strcspn(third_string, first_symbol) == my_strcspn(third_string, first_symbol));
    failed += !(strcspn(third_string, last_symbol) == my_strcspn(third_string, last_symbol));
    failed += !(strcspn(third_string, random_symbol) == my_strcspn(third_string, random_symbol));
    failed += !(strcspn(third_string, no_entry) == my_strcspn(third_string, no_entry));

    // Tests for strpbrk

    failed += !(strpbrk(third_string, first_symbol) == my_strpbrk(third_string, first_symbol));
    failed += !(strpbrk(third_string, last_symbol) == my_strpbrk(third_string, last_symbol));
    failed += !(strpbrk(third_string, random_symbol) == my_strpbrk(third_string, random_symbol));
    failed += !(strpbrk(third_string, no_entry) == my_strpbrk(third_string, no_entry));

    printf("%d\n", failed);

    return 0;
}

size_t my_strspn(const char *s, const char *accept)
{
    size_t index = 0;

    while (*(s + index) && *(accept + index) && *(s + index) == *(accept + index))
        index++;

    return index;
}

size_t my_strcspn(const char *s, const char *reject)
{
    size_t index = 0;

    while (*(s + index) && !strchr(reject, *(s + index)))
        index++;

    return index;
}

char *my_strpbrk(const char *s, const char *accept)
{
    while (*s && !strchr(accept, *s))
        s++;

    return *s ? (char *) s : NULL;
}

