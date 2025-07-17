#include "test.h"

#define NAME_F "lib_test/test_graph.txt"

// Граф из примера в materials
#define SIZE_11 11
#define GRAF_EXAMPLE "lib_test/data/graph_examples.txt"
#define RES_D_GRAF_EXAMPLE 253
#define RES_D_GRAF_EXAMPLE_APPROX (int)(RES_D_GRAF_EXAMPLE * 1.2)

#define SIZE_5 5
#define STR_GRAPH_5 \
  "5\n0 5 6 14 15\n5 0 7 10 6\n6 7 0 8 7\n14 10 8 0 9\n15 6 7 9 0\n"
#define RES_DIST_5 34
#define RES_DIST_APPROX (int)(RES_DIST_5 * 1.2)

// Ориентированный граф
#define SIZE_4 4
#define STR_GRAPH_RING "4\n0 5 0 0\n0 0 3 0\n0 0 0 8\n4 0 0 0\n"
#define RES_DIST_RING 20

// Граф для которого нет гамильтонова цикла.
#define STR_GRAPH_4 "4\n0 2 0 0\n2 0 3 1\n0 3 0 0\n0 1 0 0\n"

// graph_examples
START_TEST(test_graph_examples) {
  Graph* graph = load_graph_from_file(GRAF_EXAMPLE);
  TSM_RESULT* res = solve_traveling_salesman_problem(graph);
  ck_assert_ptr_nonnull(res);
  ck_assert_ptr_nonnull(res->vertices);
  // Найденный путь не превышает оптимальный более чем на 20%.
  ck_assert_int_lt((int)res->distance, RES_D_GRAF_EXAMPLE_APPROX);
  ck_assert_int_ge((int)res->distance, RES_D_GRAF_EXAMPLE);

  // Проверяем что все вершины посещены.
  int set[SIZE_11] = {0};
  int vertex_sum = 0;
  for (int i = 0; i < SIZE_11 + 1; i++) set[res->vertices[i]] = 1;
  for (int i = 0; i < SIZE_11; i++) vertex_sum += set[i];
  ck_assert_int_eq(vertex_sum, SIZE_11);

  // Проверяем что сумма растояний вершин соответствует дистанции
  int dist_sum = 0;
  int size = get_size_graph(graph);
  const int** matrix = get_matrix_graph(graph);
  for (int i = 0; i < size; i++)
    dist_sum += matrix[res->vertices[i]][res->vertices[i + 1]];
  ck_assert_int_eq(dist_sum, res->distance);

  free_tsm_result(res);
  free_graph(graph);
}
END_TEST

// Проверка корректной работы алгоритма.
START_TEST(test_normal_work_size_5) {
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_GRAPH_5);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  TSM_RESULT* res = solve_traveling_salesman_problem(graph);
  ck_assert_ptr_nonnull(res);
  ck_assert_ptr_nonnull(res->vertices);
  // Найденный путь не превышает оптимальный более чем на 20%.
  ck_assert_int_lt((int)res->distance, RES_DIST_APPROX);
  ck_assert_int_ge((int)res->distance, RES_DIST_5);

  // Проверяем что все вершины посещены.
  int set[SIZE_5] = {0};
  int vertex_sum = 0;
  for (int i = 0; i < SIZE_5 + 1; i++) set[res->vertices[i]] = 1;
  for (int i = 0; i < SIZE_5; i++) vertex_sum += set[i];
  ck_assert_int_eq(vertex_sum, SIZE_5);

  // Проверяем что сумма растояний вершин соответствует дистанции
  int dist_sum = 0;
  int size = get_size_graph(graph);
  const int** matrix = get_matrix_graph(graph);
  for (int i = 0; i < size; i++)
    dist_sum += matrix[res->vertices[i]][res->vertices[i + 1]];
  ck_assert_int_eq(dist_sum, res->distance);

  free_tsm_result(res);
  free_graph(graph);
}
END_TEST

// Проверка корректной работы c ориентированным графом.
START_TEST(test_work_ring) {
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_GRAPH_RING);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  TSM_RESULT* res = solve_traveling_salesman_problem(graph);
  ck_assert_ptr_nonnull(res);
  ck_assert_ptr_nonnull(res->vertices);
  ck_assert_int_eq((int)res->distance, RES_DIST_RING);

  // Проверяем что все вершины посещены.
  int set[SIZE_4] = {0};
  int vertex_sum = 0;
  for (int i = 0; i < SIZE_4 + 1; i++) set[res->vertices[i]] = 1;
  for (int i = 0; i < SIZE_4; i++) vertex_sum += set[i];
  ck_assert_int_eq(vertex_sum, SIZE_4);

  // Проверяем что сумма растояний вершин соответствует дистанции
  int dist_sum = 0;
  int size = get_size_graph(graph);
  const int** matrix = get_matrix_graph(graph);
  for (int i = 0; i < size; i++)
    dist_sum += matrix[res->vertices[i]][res->vertices[i + 1]];
  ck_assert_int_eq(dist_sum, res->distance);

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
  TSM_RESULT* res = solve_traveling_salesman_problem(graph);
  ck_assert_ptr_null(res);

  free_tsm_result(res);
  free_graph(graph);
}
END_TEST

Suite* test_solve_traveling_salesman_problem(void) {
  Suite* s = suite_create("\033[1;35mTsp_ant_coluny\033[0m");
  TCase* tc = tcase_create("TSP_ant_colony");

  tcase_add_test(tc, test_graph_examples);
  tcase_add_test(tc, test_normal_work_size_5);
  tcase_add_test(tc, test_work_ring);
  tcase_add_test(tc, test_not_find_path);
  suite_add_tcase(s, tc);
  return s;
}