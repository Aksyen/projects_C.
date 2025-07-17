#include <check.h>

#include "graph.h"

#define NAME_F "test_graph.txt"
#define NAME_F_DOT "test_graph.dot"
#define SIZE 4
#define STR_GRAPH "4\n0 2 0 0\n2 0 3 4\n0 3 0 0\n0 4 0 0\n"
#define STR_GRAPH_DOT \
  "graph graphname {\n\
	a -- b [label=2];\n\
	b -- c [label=3];\n\
	b -- d [label=4];\n\
}"
#define GRAPH                                                \
  {                                                          \
    {0, 2, 0, 0}, {2, 0, 3, 4}, {0, 3, 0, 0}, { 0, 4, 0, 0 } \
  }

#define STR_DIGRAPH "4\n0 2 0 0\n0 0 3 4\n0 0 0 0\n0 0 0 0\n"
#define STR_DIGRAPH_DOT \
  "digraph graphname {\n\
	a -> b [label=2];\n\
	b -> c [label=3];\n\
	b -> d [label=4];\n\
}"

#define DIGRAPH                                              \
  {                                                          \
    {0, 2, 0, 0}, {0, 0, 3, 4}, {0, 0, 0, 0}, { 0, 0, 0, 0 } \
  }

#define WRONG_SIZE_STR_GRAPH "-4\n0 2 0 0\n2 0 3 4\n0 3 0 0\n0 4 1 0\n"
#define WRONG_STR_GRAPH "4\n0 -2 0 0\n2 0 3 4\n0 3 0 0\n0 4 0 0\n"
#define WRONG_GRAPH                                           \
  {                                                           \
    {0, -2, 0, 0}, {2, 0, 3, 4}, {0, 3, 0, 0}, { 0, 4, 0, 0 } \
  }

#define STR_GRAPH_CUSTOM "4\n0 1 3 0\n1 0 2 0\n3 2 0 4\n0 0 4 0\n"
#define STR_GRAPH_CUSTOM_DOT \
  "graph graphname {\n\
	a -- b [label=1];\n\
	a -- c [label=3];\n\
	b -- c [label=2];\n\
	c -- d [label=4];\n\
}"

#define STR_DIGRAPH_CUSTOM "4\n0 5 0 0\n0 0 6 0\n7 0 0 8\n0 0 0 0\n"
#define STR_DIGRAPH_CUSTOM_DOT \
  "digraph graphname {\n\
	a -> b [label=5];\n\
	b -> c [label=6];\n\
	c -> a [label=7];\n\
	c -> d [label=8];\n\
}"

// Проверка корректной инициализации гарфа из файла.
START_TEST(test_load_graph_from_file) {
  int matrix[SIZE][SIZE] = GRAPH;
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_GRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  ck_assert_ptr_nonnull(graph->matrix);
  ck_assert_ptr_nonnull(graph);
  ck_assert_int_eq(graph->size, SIZE);

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      ck_assert_int_eq(graph->matrix[i][j], matrix[i][j]);
    }
  }
  free_graph(graph);
}
END_TEST

// Невозможно открыть файл.
START_TEST(test_not_load_graph_from_file) {
  const char* file_name = "nondir/" NAME_F;

  Graph* graph = load_graph_from_file(file_name);
  ck_assert_ptr_null(graph);
}
END_TEST

// Передан нулевой указатель на строку.
START_TEST(test_not_load_graph_from_file2) {
  Graph* graph = load_graph_from_file((char*)NULL);
  ck_assert_ptr_null(graph);
}
END_TEST

// Некорректный формат данных.
START_TEST(test_wrong_data_load_graph_from_file) {
  // Размер не натуральное чилсо.
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, WRONG_SIZE_STR_GRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  ck_assert_ptr_null(graph);

  // Веса не натуральные чилса.
  f = fopen(NAME_F, "w");
  fprintf(f, WRONG_STR_GRAPH);
  fclose(f);

  graph = load_graph_from_file(NAME_F);
  ck_assert_ptr_null(graph);
}
END_TEST

// Некорректные данные при выделении памяти для матрицы графа.
START_TEST(test_create_graph_incorrect_param) {
  Graph* graph = create_graph(-4);
  ck_assert_ptr_null(graph);
}
END_TEST

// Експорт гарф в .dot.
START_TEST(test_export_graph_to_dot) {
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_GRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);

  int status = export_graph_to_dot(NAME_F_DOT, graph);
  free_graph(graph);
  ck_assert_int_eq(status, 0);

  // Сравнение контрольных данных с данными записанными в файл
  const char* expected = STR_GRAPH_DOT;
  int size_str = strlen(expected);
  char* buff = calloc(size_str + 1, sizeof(char));
  f = fopen(NAME_F_DOT, "r");
  int size_f = fread(buff, 1, size_str, f);
  fclose(f);
  ck_assert_int_eq(size_str, size_f);
  ck_assert_str_eq(expected, buff);
  free(buff);
}
END_TEST

// Експорт дигарф в .dot.
START_TEST(test_export_digraph_to_dot) {
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_DIGRAPH);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);

  int status = export_graph_to_dot(NAME_F_DOT, graph);
  free_graph(graph);
  ck_assert_int_eq(status, 0);

  // Сравнение контрольных данных с данными записанными в файл
  const char* s_ddot = STR_DIGRAPH_DOT;
  int size_str = strlen(s_ddot);
  char* buff = calloc(size_str + 1, sizeof(char));
  f = fopen(NAME_F_DOT, "r");
  int size_f = fread(buff, 1, size_str, f);
  fclose(f);
  ck_assert_int_eq(size_str, size_f);
  ck_assert_int_eq(strcmp(s_ddot, buff), 0);
  free(buff);
}
END_TEST

// Неверные параметры.
START_TEST(test_export_digraph_to_dot_incorrect_param) {
  int status = export_graph_to_dot((char*)NULL, (Graph*)NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

// Невозможно открыть файл.
START_TEST(test_export_digraph_to_dot_not_open_f) {
  Graph* graph = create_graph(SIZE);

  const char* wron_f = "blabla/" NAME_F_DOT;
  int status = export_graph_to_dot(wron_f, graph);
  ck_assert_int_eq(status, 1);
  free_graph(graph);
}
END_TEST

START_TEST(test_export_graph_with_weights) {
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_GRAPH_CUSTOM);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  ck_assert_ptr_nonnull(graph);

  int status = export_graph_to_dot(NAME_F_DOT, graph);
  free_graph(graph);
  ck_assert_int_eq(status, 0);

  const char* expected = STR_GRAPH_CUSTOM_DOT;
  int len = strlen(expected);
  char* buf = calloc(len + 1, sizeof(char));
  f = fopen(NAME_F_DOT, "r");
  int read_size = fread(buf, 1, len, f);
  fclose(f);

  ck_assert_int_eq(read_size, len);
  ck_assert_str_eq(buf, expected);
  free(buf);
}
END_TEST

START_TEST(test_export_digraph_with_weights) {
  FILE* f = fopen(NAME_F, "w");
  fprintf(f, STR_DIGRAPH_CUSTOM);
  fclose(f);

  Graph* graph = load_graph_from_file(NAME_F);
  ck_assert_ptr_nonnull(graph);

  int status = export_graph_to_dot(NAME_F_DOT, graph);
  free_graph(graph);
  ck_assert_int_eq(status, 0);

  const char* expected = STR_DIGRAPH_CUSTOM_DOT;
  int len = strlen(expected);
  char* buf = calloc(len + 1, sizeof(char));
  f = fopen(NAME_F_DOT, "r");
  int read_size = fread(buf, 1, len, f);
  fclose(f);

  ck_assert_int_eq(read_size, len);
  ck_assert_str_eq(buf, expected);
  free(buf);
}
END_TEST

Suite* graph_suite(void) {
  Suite* s = suite_create("Graph");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_load_graph_from_file);
  tcase_add_test(tc_core, test_not_load_graph_from_file);
  tcase_add_test(tc_core, test_not_load_graph_from_file2);
  tcase_add_test(tc_core, test_wrong_data_load_graph_from_file);
  tcase_add_test(tc_core, test_create_graph_incorrect_param);
  tcase_add_test(tc_core, test_export_graph_to_dot);
  tcase_add_test(tc_core, test_export_digraph_to_dot);
  tcase_add_test(tc_core, test_export_digraph_to_dot_incorrect_param);
  tcase_add_test(tc_core, test_export_digraph_to_dot_not_open_f);
  tcase_add_test(tc_core, test_export_graph_with_weights);
  tcase_add_test(tc_core, test_export_digraph_with_weights);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int failed;
  Suite* s = graph_suite();
  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  const char* red = "\033[1;91m";
  const char* green = "\033[1;32m";
  printf("=========%s FAILED \033[0m: %d =========\n", failed ? red : green,
         failed);

  return (failed == 0) ? 0 : 1;
}
