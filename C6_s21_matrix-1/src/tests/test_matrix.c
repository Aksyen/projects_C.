#include "test_matrix.h"

int main(void) {
  int failed = 0;
  Suite *s21_matrix_test[] = {test_create_remove(),
                              test_eq_matrix(),
                              test_transpose(),
                              test_sum_matrix(),
                              test_sub_matrix(),
                              test_mult_number(),
                              test_mult_matrix(),
                              test_determinant(),
                              test_calc_complements(),
                              test_inverse_matrix(),
                              NULL};

  for (int i = 0; s21_matrix_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_matrix_test[i]);

    srunner_set_fork_status(sr, CK_FORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  if (failed)
    printf("\033[0;41m========= TESTS FAILED: %d =========\033[0m\n", failed);
  else
    printf("\033[0;32m========= TESTS SUCCESS: =========\033[0m\n");

  return 0;
}
