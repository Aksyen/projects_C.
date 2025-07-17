#include "test.h"

#define NAME_DIJKSTRA_FILE "lib_test/dijkstra_graph.txt"

#define STR_DIJKSTRA_GRAPH \
  "5\n0 1 4 0 0\n1 0 0 2 0\n4 0 0 1 1\n0 2 1 0 0\n0 0 1 0 0\n"
#define SHORTEST_0_3 3
#define SHORTEST_0_4 5
#define SHORTEST_1_2 -1  // нет пути из 1 в 2 в направленном графе

#define STR_DIJKSTRA_GRAPH2 \
  "5\n"                     \
  "0 1 4 0 0\n"             \
  "0 0 0 2 0\n"             \
  "0 0 0 1 1\n"             \
  "0 0 0 0 0\n"             \
  "0 0 0 0 0\n"

START_TEST(test_dijkstra_shortest_path_basic) {
  FILE* f = fopen(NAME_DIJKSTRA_FILE, "w");
  fprintf(f, STR_DIJKSTRA_GRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_DIJKSTRA_FILE);
  ck_assert_ptr_nonnull(graph);

  int d = get_shortest_path_between_vertices(graph, 0, 3);
  ck_assert_int_eq(d, SHORTEST_0_3);

  d = get_shortest_path_between_vertices(graph, 0, 4);
  ck_assert_int_eq(d, SHORTEST_0_4);

  free_graph(graph);
}
END_TEST

START_TEST(test_dijkstra_no_path) {
  FILE* f = fopen(NAME_DIJKSTRA_FILE, "w");
  fprintf(f, STR_DIJKSTRA_GRAPH2);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_DIJKSTRA_FILE);
  ck_assert_ptr_nonnull(graph);

  int d = get_shortest_path_between_vertices(graph, 1, 2);
  ck_assert_int_eq(d, SHORTEST_1_2);  // -1

  free_graph(graph);
}
END_TEST

START_TEST(test_dijkstra_invalid_input) {
  const Graph* null_graph = NULL;
  int d = get_shortest_path_between_vertices(null_graph, 0, 1);
  ck_assert_int_eq(d, -1);

  Graph* graph = create_graph(3);
  ck_assert_ptr_nonnull(graph);

  d = get_shortest_path_between_vertices(graph, -1, 0);
  ck_assert_int_eq(d, -1);

  d = get_shortest_path_between_vertices(graph, 0, 3);
  ck_assert_int_eq(d, -1);

  free_graph(graph);
}
END_TEST

Suite* test_get_shortest_path_between_vertices(void) {
  Suite* s = suite_create("\033[35mget_shortest_path_between_vertices\033[0m");
  TCase* tc = tcase_create("get_shortest_path_between_vertices");

  tcase_add_test(tc, test_dijkstra_shortest_path_basic);
  tcase_add_test(tc, test_dijkstra_no_path);
  tcase_add_test(tc, test_dijkstra_invalid_input);

  suite_add_tcase(s, tc);
  return s;
}