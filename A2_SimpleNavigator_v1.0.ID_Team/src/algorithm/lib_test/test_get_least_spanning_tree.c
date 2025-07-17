#include "test.h"

#define NAME_PRIM_FILE "lib_test/prim_graph.txt"

#define STR_PRIM_GRAPH \
  "5\n0 2 0 6 0\n2 0 3 8 5\n0 3 0 0 7\n6 8 0 0 9\n0 5 7 9 0\n"
#define EXPECTED_PRIM_MATRIX                                              \
  {                                                                       \
    {0, 2, 0, 6, 0}, {2, 0, 3, 0, 5}, {0, 3, 0, 0, 0}, {6, 0, 0, 0, 0}, { \
      0, 5, 0, 0, 0                                                       \
    }                                                                     \
  }

START_TEST(test_prim_basic) {
  FILE* f = fopen(NAME_PRIM_FILE, "w");
  fprintf(f, STR_PRIM_GRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_PRIM_FILE);
  ck_assert_ptr_nonnull(graph);

  int** mst = get_least_spanning_tree(graph);
  ck_assert_ptr_nonnull(mst);

  int expected[5][5] = {{0, 2, 0, 6, 0},
                        {2, 0, 3, 0, 5},
                        {0, 3, 0, 0, 0},
                        {6, 0, 0, 0, 0},
                        {0, 5, 0, 0, 0}};

  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j) ck_assert_int_eq(mst[i][j], expected[i][j]);

  remove_matrix(mst, 5);
  free_graph(graph);
}
END_TEST

START_TEST(test_prim_null_graph) {
  int** mst = get_least_spanning_tree(NULL);
  ck_assert_ptr_null(mst);
}
END_TEST

START_TEST(test_prim_disconnected_graph) {
  Graph* graph = create_graph(4);
  ck_assert_ptr_nonnull(graph);

  // Только 0 — 1 и 1 — 2 связаны
  graph->matrix[0][1] = 1;
  graph->matrix[1][0] = 1;
  graph->matrix[1][2] = 2;
  graph->matrix[2][1] = 2;

  int** mst = get_least_spanning_tree(graph);
  ck_assert_ptr_nonnull(mst);

  // Ребро к вершине 3 должно отсутствовать
  ck_assert_int_eq(mst[3][0], 0);
  ck_assert_int_eq(mst[3][1], 0);
  ck_assert_int_eq(mst[3][2], 0);
  ck_assert_int_eq(mst[3][3], 0);

  remove_matrix(mst, 4);
  free_graph(graph);
}
END_TEST

Suite* test_get_least_spanning_tree(void) {
  Suite* s = suite_create("\033[35mget_least_spanning_tree\033[0m");
  TCase* tc = tcase_create("get_least_spanning_tree");

  tcase_add_test(tc, test_prim_basic);
  tcase_add_test(tc, test_prim_null_graph);
  tcase_add_test(tc, test_prim_disconnected_graph);

  suite_add_tcase(s, tc);
  return s;
}
