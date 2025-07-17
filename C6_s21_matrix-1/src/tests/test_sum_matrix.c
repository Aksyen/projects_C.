#include "test_matrix.h"

START_TEST(test_s21_sum_matrix_valid) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Заполняем матрицы значениями
  double counter = 1.0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = counter;
      B.matrix[i][j] = counter + 1.0;
      counter += 1.0;
    }
  }

  // Ожидаемое суммирование
  int sum_result = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(sum_result, OK);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(result.matrix[i][j], A.matrix[i][j] + B.matrix[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_sum_matrix_invalid_size) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 3, &B);  // Матрицы разного размера

  // Заполнение значениями
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 1.0;
    }
  }
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = 2.0;
    }
  }

  int sum_result = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(sum_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sum_matrix_null_pointer) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Заполнение значениями
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 1.0;
      B.matrix[i][j] = 2.0;
    }
  }

  // Проверка с NULL
  int sum_result = s21_sum_matrix(NULL, &B, &result);
  ck_assert_int_eq(sum_result, INCORRECT_MATRIX);

  sum_result = s21_sum_matrix(&A, NULL, &result);
  ck_assert_int_eq(sum_result, INCORRECT_MATRIX);

  sum_result = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(sum_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sum_matrix_empty_matrix) {
  matrix_t A = {NULL, 0, 0};  // Симуляция пустой матрицы
  matrix_t B = {NULL, 0, 0};
  matrix_t result;

  int sum_result = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(sum_result, INCORRECT_MATRIX);  // Ожидаем код ошибки
}
END_TEST

START_TEST(test_s21_sum_matrix_overflow) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // Заполняем матрицы значениями, которые приведут к переполнению
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      // Максимальные значение для double
      A.matrix[i][j] = DBL_MAX;
      B.matrix[i][j] = DBL_MAX;
    }
  }

  int sum_result = s21_sum_matrix(&A, &B, &result);
  // Ожидаем ошибку переполнения
  ck_assert_int_eq(sum_result, CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *test_sum_matrix(void) {
  Suite *s = suite_create("\033[35ms21_sum_matrix\033[0m");
  TCase *tc_core = tcase_create("sum_matrix_tc");

  // Добавляем тесты в тестовый случай
  tcase_add_test(tc_core, test_s21_sum_matrix_valid);
  tcase_add_test(tc_core, test_s21_sum_matrix_invalid_size);
  tcase_add_test(tc_core, test_s21_sum_matrix_null_pointer);
  tcase_add_test(tc_core, test_s21_sum_matrix_empty_matrix);
  tcase_add_test(tc_core, test_s21_sum_matrix_overflow);

  suite_add_tcase(s, tc_core);

  return s;
}
