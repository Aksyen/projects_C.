#include "test.h"

#define NAME_F "lib_test/test_graph.txt"

#define SIZE_11 11
#define GRAF_EXAMPLE "lib_test/data/graph_examples.txt"
#define RES_D_GRAF_EXAMPLE 253

// Ориентированный граф
#define SIZE_4 4
#define STR_GRAPH_RING "4\n0 5 0 0\n0 0 3 0\n0 0 0 8\n4 0 0 0\n"
#define RES_DIST_RING 20
#define RES_VERT_RING {0, 1, 2, 3, 0}

#define SIZE_5 5
#define STR_GRAPH_5 \
  "5\n0 5 6 14 15\n5 0 7 10 6\n6 7 0 8 7\n14 10 8 0 9\n15 6 7 9 0\n"
#define RES_DIST_5 34
#define RES_VERT_5 {0, 2, 3, 4, 1, 0}

// Граф для которого нет гамильтонова цикла.
#define STR_GRAPH_4 "4\n0 2 0 0\n2 0 3 1\n0 3 0 0\n0 1 0 0\n"

// Проверка корректной работы алгоритма.
START_TEST(test_graf_example) {
  Graph* graph = load_graph_from_file(GRAF_EXAMPLE);
  TSM_RESULT* res = solve_tsp_held_karp(graph);
  ck_assert_ptr_nonnull(res);
  ck_assert_ptr_nonnull(res->vertices);
  ck_assert_int_eq((int)res->distance, RES_D_GRAF_EXAMPLE);

  // Проверяем что сумма растояний вершин соответствует дистанции
  int dist_sum = 0;
  int size = get_size_graph(graph);
  const int** matrix = get_matrix_graph(graph);
  for (int i = 0; i < size; i++)
    dist_sum += matrix[res->vertices[i]][res->vertices[i + 1]];
  ck_assert_int_eq(dist_sum, RES_D_GRAF_EXAMPLE);

  free_tsm_result(res);
  free_graph(graph);
}
END_TEST

// Проверка корректной работы алгоритма.
START_TEST(test_normal_work_size_5) {
  int expected_vertices[SIZE_5 + 1] = RES_VERT_5;
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_GRAPH_5);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  TSM_RESULT* res = solve_tsp_held_karp(graph);
  ck_assert_ptr_nonnull(res);
  ck_assert_ptr_nonnull(res->vertices);
  ck_assert_int_eq((int)res->distance, RES_DIST_5);

  for (int i = 0; i < SIZE_5 + 1; i++) {
    ck_assert_int_eq(res->vertices[i], expected_vertices[i]);
  }
  free_tsm_result(res);
  free_graph(graph);
}
END_TEST

// Проверка корректной работы c ориентированным графом.
START_TEST(test_work_ring) {
  int expected_vertices[SIZE_4 + 1] = RES_VERT_RING;
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_GRAPH_RING);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  TSM_RESULT* res = solve_tsp_held_karp(graph);
  ck_assert_ptr_nonnull(res);
  ck_assert_ptr_nonnull(res->vertices);
  ck_assert_int_eq((int)res->distance, RES_DIST_RING);

  for (int i = 0; i < SIZE_4 + 1; i++) {
    ck_assert_int_eq(res->vertices[i], expected_vertices[i]);
  }
  free_tsm_result(res);
  free_graph(graph);
}
END_TEST

// Путь не может быть найден.
START_TEST(test_not_find_path) {
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_GRAPH_4);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  TSM_RESULT* res = solve_tsp_held_karp(graph);
  ck_assert_ptr_null(res);
  free_tsm_result(res);
  free_graph(graph);
}
END_TEST

Suite* test_tsp_held_karp(void) {
  Suite* s = suite_create("\033[1;35mTsp_held_karp\033[0m");
  TCase* tc = tcase_create("TSP_held_karp");

  tcase_add_test(tc, test_graf_example);
  tcase_add_test(tc, test_normal_work_size_5);
  tcase_add_test(tc, test_work_ring);
  tcase_add_test(tc, test_not_find_path);
  suite_add_tcase(s, tc);
  return s;
}