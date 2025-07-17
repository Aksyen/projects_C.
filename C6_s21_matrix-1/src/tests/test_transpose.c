#include "test_matrix.h"

START_TEST(test_s21_transpose_square_matrix) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  // Заполняем матрицу значениями
  double counter = 1.0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = counter++;
    }
  }

  int trans_result = s21_transpose(&A, &result);
  ck_assert_int_eq(trans_result, 0);  // Ожидаем успешное выполнение функции

  // Проверяем, что матрица была транспонирована правильно
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[2][1], 6.0);
  ck_assert_double_eq(result.matrix[1][2], 8.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_transpose_rectangular_matrix) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  // Заполняем матрицу значениями
  double counter = 1.0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = counter++;
    }
  }

  int trans_result = s21_transpose(&A, &result);
  ck_assert_int_eq(trans_result, 0);  // Ожидаем успешное выполнение функции

  // Проверяем, что матрица была транспонирована правильно
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[2][1], 6.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_transpose_one_element_matrix) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 42.0;

  int trans_result = s21_transpose(&A, &result);
  ck_assert_int_eq(trans_result, 0);  // Ожидаем успешное выполнение функции

  // Проверяем, что матрица была транспонирована правильно
  ck_assert_double_eq(result.matrix[0][0], 42.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_transpose_null_matrix) {
  matrix_t result;

  // Проверка поведения при передаче NULL указателя на матрицу
  int trans_result = s21_transpose(NULL, &result);
  ck_assert_int_eq(trans_result, 1);  // Ожидаем ошибку

  trans_result = s21_transpose(NULL, NULL);
  ck_assert_int_eq(trans_result, 1);  // Ожидаем ошибку
}
END_TEST

START_TEST(test_s21_transpose_empty_matrix) {
  matrix_t A = {NULL, 0, 0};  // Симуляция пустой матрицы
  matrix_t result;

  int trans_result = s21_transpose(&A, &result);
  ck_assert_int_eq(
      trans_result,
      INCORRECT_MATRIX);  // Ожидаем код ошибки, так как матрица пустая
}
END_TEST

Suite *test_transpose(void) {
  Suite *s = suite_create("\033[35ms21_eq_matrix\033[0m");
  TCase *tc_core = tcase_create("transpose_tc");

  // Добавляем тесты в тестовый случай
  tcase_add_test(tc_core, test_s21_transpose_square_matrix);
  tcase_add_test(tc_core, test_s21_transpose_rectangular_matrix);
  tcase_add_test(tc_core, test_s21_transpose_one_element_matrix);
  tcase_add_test(tc_core, test_s21_transpose_null_matrix);
  tcase_add_test(tc_core, test_s21_transpose_empty_matrix);

  suite_add_tcase(s, tc_core);

  return s;
}