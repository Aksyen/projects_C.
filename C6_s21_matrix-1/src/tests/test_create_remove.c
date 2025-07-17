#include "test_matrix.h"

START_TEST(test_s21_create_matrix_valid) {
  matrix_t A;
  int result = s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_ptr_nonnull(A.matrix);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j;  // Заполнение матрицы для дополнительной проверки
    }
  }

  // Проверка значений в матрице
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(A.matrix[i][j], i + j);
    }
  }

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_invalid_size) {
  matrix_t A;
  int result = s21_create_matrix(-3, 3, &A);
  ck_assert_int_eq(result, 1);

  result = s21_create_matrix(3, -3, &A);
  ck_assert_int_eq(result, 1);

  result = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_create_matrix_null_result) {
  int result = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_remove_matrix_valid) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_s21_remove_matrix_null) {
  // Тест на корректное освобождение памяти при корректных данных
  matrix_t A = {NULL, 3, 3};
  s21_remove_matrix(&A);
  // Размеры останутся неизменными, если матрица изначально NULL
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 3);
  // Размеры останутся неизменными, если матрица изначально NULL
  ck_assert_int_eq(A.columns, 3);

  // Тест на передачу NULL в качестве параметра функции
  s21_remove_matrix(NULL);
}
END_TEST

START_TEST(test_s21_create_matrix_large_size1) {
  matrix_t A;

  // Используем размеры, которые зависят от системы, на которой тестируется код
  int rows = 1000000000;     // 1 миллиард строк
  int columns = 1000000000;  // 1 миллиард столбцов

  int result = s21_create_matrix(rows, columns, &A);
  if (result == 2) {
    ck_assert_int_eq(result, 2);  // Ожидаем ошибку в выделении памяти
    ck_assert_ptr_null(A.matrix);  // Убедиться, что матрица не была выделена
  } else
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_large_size2) {
  matrix_t A;

  // Используем размеры, которые зависят от системы, на которой тестируется код
  int rows = 2;
  int columns = 1000000000;  // 1 миллиард столбцов

  int result = s21_create_matrix(rows, columns, &A);
  if (result == 2) {
    ck_assert_int_eq(result, 2);  // Ожидаем ошибку в выделении памяти
    ck_assert_ptr_null(A.matrix);  // Убедиться, что матрица не была выделена
  } else
    s21_remove_matrix(&A);
}
END_TEST

Suite *test_create_remove(void) {
  Suite *s = suite_create("\033[35ms21_create_matrix_s21_remove_matrix\033[0m");
  TCase *tc_core = tcase_create("suite_create_tc");

  // Добавляем тесты в тестовый случай
  tcase_add_test(tc_core, test_s21_create_matrix_valid);
  tcase_add_test(tc_core, test_s21_create_matrix_invalid_size);
  tcase_add_test(tc_core, test_s21_create_matrix_null_result);
  tcase_add_test(tc_core, test_s21_remove_matrix_valid);
  tcase_add_test(tc_core, test_s21_remove_matrix_null);
  tcase_add_test(tc_core, test_s21_create_matrix_large_size1);
  tcase_add_test(tc_core, test_s21_create_matrix_large_size2);

  suite_add_tcase(s, tc_core);

  return s;
}