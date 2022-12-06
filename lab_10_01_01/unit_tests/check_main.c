#include "check_pop_front.h"
#include "check_pop_back.h"
#include "check_append.h"
#include "check_front_back_split.h"
#include "check_sort.h"
#include "check_sorted_merge.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(void)
{
    int no_failed = 0;
    Suite *pop_front_list_suite;
    Suite *pop_back_list_suite;
    Suite *append_list_suite;
    Suite *front_back_split_list_suite;
    Suite *sort_list_suite;
    Suite *sorted_merge_list_suite;
    SRunner *runner;

    pop_front_list_suite = pop_front_suite();
    pop_back_list_suite = pop_back_suite();
    append_list_suite = append_suite();
    front_back_split_list_suite = front_back_split_suite();
    sort_list_suite = sort_suite();
    sorted_merge_list_suite = sorted_merge_suite();

    runner = srunner_create(pop_front_list_suite);
    srunner_add_suite(runner, pop_back_list_suite);
    srunner_add_suite(runner, append_list_suite);
    srunner_add_suite(runner, front_back_split_list_suite);
    srunner_add_suite(runner, sort_list_suite);
    srunner_add_suite(runner, sorted_merge_list_suite);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}