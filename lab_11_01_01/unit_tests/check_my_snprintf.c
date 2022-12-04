#include <stdio.h>
#include "../inc/my_snprintf.h"
#include "check_my_snprintf.h"

// %d, %hd
// Положительное целое число
START_TEST(test_positive_digit)
{
    char str[20];
    char my_str[20];
    size_t size = 20;
    long int digit = 2147483648;

    int write = snprintf(str, size, "%d", (int) digit);
    int my_write = my_snprintf(my_str, size, "%d", (int) digit);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Отрицательное целое число
START_TEST(test_negative_digit)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%d", -24);
    int my_write = my_snprintf(my_str, size, "%d", -24);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Ноль целое число
START_TEST(test_zero_digit)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%d", 0);
    int my_write = my_snprintf(my_str, size, "%d", 0);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Положительное short целое число
START_TEST(test_short_positive_digit)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%hd", 24);
    int my_write = my_snprintf(my_str, size, "%hd", 24);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Отрицательное short целое число
START_TEST(test_short_negative_digit)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%hd", -24);
    int my_write = my_snprintf(my_str, size, "%hd", -24);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Ноль short целое число
START_TEST(test_short_zero_digit)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%hd", 0);
    int my_write = my_snprintf(my_str, size, "%hd", 0);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// %hx, %x
// Положительное целое число
START_TEST(test_hex_positive_digit)
{
    char str[20];
    char my_str[20];
    size_t size = 20;
    unsigned int digit = 4294967294;

    int write = snprintf(str, size, "%x", digit);
    int my_write = my_snprintf(my_str, size, "%x", digit);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Ноль целое число
START_TEST(test_hex_zero_digit)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%x", 0);
    int my_write = my_snprintf(my_str, size, "%x", 0);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Положительное short целое число
START_TEST(test_short_hex_positive_digit)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%hx", 24);
    int my_write = my_snprintf(my_str, size, "%hx", 24);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Ноль short целое число
START_TEST(test_short_hex_zero_digit)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%hx", 0);
    int my_write = my_snprintf(my_str, size, "%hx", 0);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// %c
START_TEST(test_char)
{
    char str[5] = "";
    char my_str[5] = "";
    size_t size = 5;

    int write = snprintf(str, size, "%c", 'f');
    int my_write = my_snprintf(my_str, size, "%c", 'f');

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// %s
START_TEST(test_string)
{
    char str[10] = "";
    char my_str[10] = "";
    size_t size = 10;

    int write = snprintf(str, size, "%s", "hello");
    int my_write = my_snprintf(my_str, size, "%s", "hello");

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// %s переполнение
START_TEST(test_overflow_string)
{
    char str[2] = "";
    char my_str[2] = "";
    size_t size = 2;
    char print[] = "hello";

    int write = snprintf(str, size, "%s", print);
    int my_write = my_snprintf(my_str, size, "%s", print);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Комбинированная форматная строка
START_TEST(test_combine_string)
{
    char str[256] = "";
    char my_str[256] = "";
    size_t size = 256;

    int write = snprintf(str, size, "Hello %s! Todau is %d or in hex %x. I like it in %hd%%\n", "world", 24, 24, 100);
    int my_write = my_snprintf(my_str, size, "Hello %s! Todau is %d or in hex %x. I like it in %hd%%\n", "world", 24, 24, 100);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

// Строка NULL, size = 0
START_TEST(test_null_string)
{
	char *str = NULL;
	char *my_str = NULL;

    int write = snprintf(str, 0, "Hello %s! Todau is %d or in hex %x. I like it in %hd%%\n", "world", 24, 24, 100);
    int my_write = my_snprintf(my_str, 0, "Hello %s! Todau is %d or in hex %x. I like it in %hd%%\n", "world", 24, 24, 100);

    ck_assert_int_eq(write, my_write);
    ck_assert_ptr_null(str);
    ck_assert_ptr_null(my_str);
}
END_TEST

// %s переполнение
START_TEST(test_null_format)
{
    char str[10] = "";
    char my_str[10] = "";
    size_t size = 10;
    char print[] = "hello";
    char *format = NULL;

    int write = snprintf(str, size, format, print);
    int my_write = my_snprintf(my_str, size, format, print);

    ck_assert_int_eq(write, my_write);
    ck_assert_str_eq(str, my_str);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("my_snprintf_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_positive_digit);
    tcase_add_test(tc_pos, test_negative_digit);
    tcase_add_test(tc_pos, test_zero_digit);
    tcase_add_test(tc_pos, test_short_positive_digit);
    tcase_add_test(tc_pos, test_short_negative_digit);
    tcase_add_test(tc_pos, test_short_zero_digit);

    tcase_add_test(tc_pos, test_hex_positive_digit);
    tcase_add_test(tc_pos, test_hex_zero_digit);
    tcase_add_test(tc_pos, test_short_hex_positive_digit);
    tcase_add_test(tc_pos, test_short_hex_zero_digit);

    tcase_add_test(tc_pos, test_char);
    tcase_add_test(tc_pos, test_string);
    tcase_add_test(tc_pos, test_overflow_string);
    tcase_add_test(tc_pos, test_combine_string);
    tcase_add_test(tc_pos, test_null_string);
    tcase_add_test(tc_pos, test_null_format);

    suite_add_tcase(s, tc_pos);

    return s;
}
