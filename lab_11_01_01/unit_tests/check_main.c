#include "check_my_snprintf.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(void)
{
    int no_failed = 0;
    Suite *snprintf_suite;

    SRunner *runner;

    snprintf_suite = my_snprintf_suite();

    runner = srunner_create(snprintf_suite);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}