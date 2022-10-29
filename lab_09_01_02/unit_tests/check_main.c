#include "check_copy_names_startswith.h"
#include "check_sort_container.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(void)
{
    int no_failed = 0;
    Suite *copy_suite;
    Suite *sort_suite;
    SRunner *runner;

    copy_suite = copy_names_suite();
    sort_suite = sort_container_suite();

    runner = srunner_create(copy_suite);
    srunner_add_suite(runner, sort_suite);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}