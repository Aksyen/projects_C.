#include "test.h"

#define NAME_DFS_FILE "lib_test/dfs_graph.txt"
#define STR_DFS_GRAPH "4\n0 1 0 1\n1 0 1 1\n0 1 0 1\n1 1 1 0\n"
#define EXPECTED_DFS_ORDER {0, 1, 2, 3}

#define STR_DFS_DIGRAPH "4\n0 1 0 0\n0 0 1 0\n0 0 0 1\n0 0 0 0\n"
#define EXPECTED_DFS_DIGRAPH_ORDER {0, 1, 2, 3}

#define STR_DFS_DISCONNECTED "4\n0 1 0 0\n1 0 0 0\n0 0 0 0\n0 0 0 0\n"
#define EXPECTED_DFS_DISCONNECTED_ORDER {0, 1}

START_TEST(test_depth_first_search_basic) {
  FILE* f = fopen(NAME_DFS_FILE, "w");
  fprintf(f, STR_DFS_GRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_DFS_FILE);
  ck_assert_ptr_nonnull(graph);

  int* dfs_result = depth_first_search(graph, 0);
  ck_assert_ptr_nonnull(dfs_result);

  int expected[] = EXPECTED_DFS_ORDER;
  for (int i = 0; i < get_size_graph(graph); ++i) {
    ck_assert_int_eq(dfs_result[i], expected[i]);
  }

  free(dfs_result);
  free_graph(graph);
}
END_TEST

START_TEST(test_dfs_directed_graph) {
  FILE* f = fopen(NAME_DFS_FILE, "w");
  fprintf(f, STR_DFS_DIGRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_DFS_FILE);
  ck_assert_ptr_nonnull(graph);

  int* dfs_result = depth_first_search(graph, 0);
  ck_assert_ptr_nonnull(dfs_result);

  int expected[] = EXPECTED_DFS_DIGRAPH_ORDER;
  for (int i = 0; i < get_size_graph(graph); ++i) {
    ck_assert_int_eq(dfs_result[i], expected[i]);
  }

  free(dfs_result);
  free_graph(graph);
}
END_TEST

START_TEST(test_dfs_disconnected_graph) {
  FILE* f = fopen(NAME_DFS_FILE, "w");
  fprintf(f, STR_DFS_DISCONNECTED);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_DFS_FILE);
  ck_assert_ptr_nonnull(graph);

  int* dfs_result = depth_first_search(graph, 0);
  ck_assert_ptr_nonnull(dfs_result);

  int expected[] = EXPECTED_DFS_DISCONNECTED_ORDER;
  for (int i = 0; i < 2; ++i) {
    ck_assert_int_eq(dfs_result[i], expected[i]);
  }

  free(dfs_result);
  free_graph(graph);
}
END_TEST

START_TEST(test_dfs_invalid_input) {
  const Graph* null_graph = NULL;
  int* result = depth_first_search(null_graph, 0);
  ck_assert_ptr_null(result);

  Graph* graph = create_graph(3);
  ck_assert_ptr_nonnull(graph);

  result = depth_first_search(graph, -1);
  ck_assert_ptr_null(result);

  result = depth_first_search(graph, 3);  // за пределами
  ck_assert_ptr_null(result);

  free_graph(graph);
}
END_TEST

Suite* test_depth_first_search(void) {
  Suite* s = suite_create("\033[35mdepth_first_search\033[0m");
  TCase* tc = tcase_create("depth_first_search");

  tcase_add_test(tc, test_depth_first_search_basic);
  tcase_add_test(tc, test_dfs_directed_graph);
  tcase_add_test(tc, test_dfs_disconnected_graph);
  tcase_add_test(tc, test_dfs_invalid_input);

  suite_add_tcase(s, tc);
  return s;
}
