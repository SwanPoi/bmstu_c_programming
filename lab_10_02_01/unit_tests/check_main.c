#include "check_pop_front.h"
#include "check_append.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(void)
{
    int no_failed = 0;
    Suite *pop_front_list_suite;
    Suite *append_list_suite;

    SRunner *runner;

    pop_front_list_suite = pop_front_suite();
    append_list_suite = append_suite();


    runner = srunner_create(pop_front_list_suite);
    srunner_add_suite(runner, append_list_suite);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
