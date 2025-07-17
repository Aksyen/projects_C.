#include "test_matrix.h"

START_TEST(test_s21_mult_number_valid) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  // Заполняем матрицу значениями
  double counter = 1.0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = counter;
      counter += 1.0;
    }
  }

  // Умножаем на 2.0
  int mult_result = s21_mult_number(&A, 2.0, &result);
  ck_assert_int_eq(mult_result, OK);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(result.matrix[i][j], A.matrix[i][j] * 2.0);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_zero) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  // Заполняем матрицу значениями
  double counter = 1.0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = counter;
      counter += 1.0;
    }
  }

  // Умножаем на 0
  int mult_result = s21_mult_number(&A, 0.0, &result);
  ck_assert_int_eq(mult_result, OK);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(result.matrix[i][j], 0.0);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_invalid_matrix) {
  matrix_t result;

  // Проверка с NULL указателем на матрицу
  int mult_result = s21_mult_number(NULL, 2.0, &result);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  // Проверка с NULL указателем на результат
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  mult_result = s21_mult_number(&A, 2.0, NULL);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_mult_number_overflow) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  // Заполняем матрицу значениями, которые приведут к переполнению
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = DBL_MAX;  // Значение близкое к пределу
    }
  }

  // Умножаем на 2.0, что приведет к переполнению
  int mult_result = s21_mult_number(&A, 2.0, &result);
  // Ожидаем ошибку переполнения
  ck_assert_int_eq(mult_result, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

Suite *test_mult_number(void) {
  Suite *s = suite_create("\033[35ms21_mult_number\033[0m");
  TCase *tc_core = tcase_create("mult_number_tc");

  // Добавляем тесты в тестовый случай
  tcase_add_test(tc_core, test_s21_mult_number_valid);
  tcase_add_test(tc_core, test_s21_mult_number_zero);
  tcase_add_test(tc_core, test_s21_mult_number_invalid_matrix);
  tcase_add_test(tc_core, test_s21_mult_number_overflow);

  suite_add_tcase(s, tc_core);

  return s;
}
