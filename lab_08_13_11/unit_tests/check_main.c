#include "check_matr_multiplication.h"
#include "check_matr_addition.h"
#include "check_matrix_determinant.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(void)
{
    int no_failed = 0;
    Suite *mult_suite;
    Suite *add_suite;
    Suite *det_suite;
    SRunner *runner;

    mult_suite = multiplication_suite();
    add_suite = addition_suite();
    det_suite = determinant_suite();

    runner = srunner_create(mult_suite);
    srunner_add_suite(runner, add_suite);
    srunner_add_suite(runner, det_suite);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
