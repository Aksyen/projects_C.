#include "test_matrix.h"

START_TEST(test_s21_calc_complements_2x2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  // Вычисляем алгебраические дополнения
  int complement_result = s21_calc_complements(&A, &result);

  ck_assert_int_eq(complement_result, OK);

  // Проверяем правильность значений
  ck_assert_double_eq(result.matrix[0][0], 4.0);
  ck_assert_double_eq(result.matrix[0][1], -3.0);
  ck_assert_double_eq(result.matrix[1][0], -2.0);
  ck_assert_double_eq(result.matrix[1][1], 1.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements_3x3) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 5.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 6.0;

  // Вычисляем алгебраические дополнения
  int complement_result = s21_calc_complements(&A, &result);

  ck_assert_int_eq(complement_result, OK);

  // Проверяем правильность значений
  ck_assert_double_eq(result.matrix[0][0], 24.0);
  ck_assert_double_eq(result.matrix[0][1], 5.0);
  ck_assert_double_eq(result.matrix[0][2], -4.0);
  ck_assert_double_eq(result.matrix[1][0], -12.0);
  ck_assert_double_eq(result.matrix[1][1], 3.0);
  ck_assert_double_eq(result.matrix[1][2], 2.0);
  ck_assert_double_eq(result.matrix[2][0], -2.0);
  ck_assert_double_eq(result.matrix[2][1], -5.0);
  ck_assert_double_eq(result.matrix[2][2], 4.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements_incorrect_matrix) {
  matrix_t A, result;
  s21_create_matrix(3, 2, &A);  // Неквадратная матрица

  // Заполняем матрицу A
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;

  // Пытаемся вычислить алгебраические дополнения
  int complement_result = s21_calc_complements(&A, &result);

  ck_assert_int_eq(complement_result, INCORRECT_MATRIX);  // Ожидаем ошибку

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_calc_complements_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 5.0;

  // Вычисляем алгебраические дополнения
  int complement_result = s21_calc_complements(&A, &result);

  ck_assert_int_eq(complement_result, OK);

  // Проверяем правильность значений (особый случай для 1x1, результат должен
  // быть 1)
  ck_assert_double_eq(result.matrix[0][0], 1.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements_3x3_2) {
  matrix_t A = {0}, check = {0}, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);

  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 5, A.matrix[2][1] = 2, A.matrix[2][2] = 1;

  check.matrix[0][0] = 0, check.matrix[0][1] = 10, check.matrix[0][2] = -20;
  check.matrix[1][0] = 4, check.matrix[1][1] = -14, check.matrix[1][2] = 8;
  check.matrix[2][0] = -8, check.matrix[2][1] = -2, check.matrix[2][2] = 4;

  ck_assert_int_eq(OK, s21_calc_complements(&A, &result));
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

Suite *test_calc_complements(void) {
  Suite *s = suite_create("\033[35ms21_calc_complements\033[0m");
  TCase *tc_core = tcase_create("calc_complements_tc");

  // Добавляем тесты для функции s21_calc_complements
  tcase_add_test(tc_core, test_s21_calc_complements_2x2);
  tcase_add_test(tc_core, test_s21_calc_complements_3x3);
  tcase_add_test(tc_core, test_s21_calc_complements_3x3_2);
  tcase_add_test(tc_core, test_s21_calc_complements_incorrect_matrix);
  tcase_add_test(tc_core, test_s21_calc_complements_1x1);

  suite_add_tcase(s, tc_core);

  return s;
}
