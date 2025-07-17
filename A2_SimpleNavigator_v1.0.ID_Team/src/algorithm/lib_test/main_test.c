#include "test.h"

int main() {
  int failed = 0;
  Suite *algorinhm_tests[] = {test_depth_first_search(),
                              test_breadth_first_search(),
                              test_get_shortest_path_between_vertices(),
                              test_get_shortest_paths_between_all_vertices(),
                              test_get_least_spanning_tree(),
                              test_tsp_held_karp(),
                              test_tsp_nearest_neighbor(),
                              test_solve_traveling_salesman_problem(),
                              NULL};

  for (int i = 0; algorinhm_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(algorinhm_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  const char *red = "\033[1;91m";
  const char *green = "\033[1;32m";
  printf("=========%s FAILED \033[0m: %d =========\n", failed ? red : green,
         failed);

  return failed == 0 ? 0 : 1;
}
