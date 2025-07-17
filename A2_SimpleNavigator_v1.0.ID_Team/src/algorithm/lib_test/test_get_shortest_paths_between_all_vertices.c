#include "test.h"

#define NAME_FLOYD_FILE "lib_test/floyd_graph.txt"

#define STR_FLOYD_GRAPH "4\n0 3 0 7\n0 0 1 0\n0 0 0 2\n0 0 0 0\n"
#define EXPECTED_FLOYD_MATRIX                                            \
  {                                                                      \
    {0, 3, 4, 6}, {INF, 0, 1, 3}, {INF, INF, 0, 2}, { INF, INF, INF, 0 } \
  }

START_TEST(test_floyd_basic) {
  FILE* f = fopen(NAME_FLOYD_FILE, "w");
  fprintf(f, STR_FLOYD_GRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_FLOYD_FILE);
  ck_assert_ptr_nonnull(graph);

  int** paths = get_shortest_paths_between_all_vertices(graph);
  ck_assert_ptr_nonnull(paths);

  int expected[4][4] = {
      {0, 3, 4, 6}, {INF, 0, 1, 3}, {INF, INF, 0, 2}, {INF, INF, INF, 0}};

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ck_assert_int_eq(paths[i][j], expected[i][j]);
    }
  }

  remove_matrix(paths, 4);
  free_graph(graph);
}
END_TEST

START_TEST(test_floyd_disconnected) {
  Graph* graph = create_graph(3);
  ck_assert_ptr_nonnull(graph);

  // Только одно ребро: 0 -> 1
  graph->matrix[0][1] = 5;

  int** paths = get_shortest_paths_between_all_vertices(graph);
  ck_assert_ptr_nonnull(paths);

  ck_assert_int_eq(paths[0][0], 0);
  ck_assert_int_eq(paths[0][1], 5);
  ck_assert_int_eq(paths[0][2], INF);
  ck_assert_int_eq(paths[1][2], INF);
  ck_assert_int_eq(paths[2][1], INF);

  remove_matrix(paths, 3);
  free_graph(graph);
}
END_TEST

START_TEST(test_floyd_null_input) {
  int** paths = get_shortest_paths_between_all_vertices(NULL);
  ck_assert_ptr_null(paths);
}
END_TEST

Suite* test_get_shortest_paths_between_all_vertices(void) {
  Suite* s =
      suite_create("\033[35mget_shortest_paths_between_all_vertices\033[0m");
  TCase* tc = tcase_create("get_shortest_paths_between_all_vertices");

  tcase_add_test(tc, test_floyd_basic);
  tcase_add_test(tc, test_floyd_disconnected);
  tcase_add_test(tc, test_floyd_null_input);

  suite_add_tcase(s, tc);
  return s;
}