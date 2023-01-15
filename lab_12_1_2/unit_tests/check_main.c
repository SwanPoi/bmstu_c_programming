#include <check.h>
#include "check_left_k_shift.h"
#include "check_get_full_squares.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(void)
{
    int no_failed = 0;
    Suite *s_suite;
    Suite *f_suite;
    SRunner *runner;

    f_suite = shift_suite();
    s_suite = square_suite();

    runner = srunner_create(f_suite);
    srunner_add_suite(runner, s_suite);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}