#include "test_matrix.h"

START_TEST(test_s21_inverse_matrix_2x2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 4.0;
  A.matrix[0][1] = 7.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 6.0;

  // Вычисляем обратную матрицу
  int inverse_result = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(inverse_result, OK);

  // Проверяем правильность значений
  ck_assert_double_eq_tol(result.matrix[0][0], 0.6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.7, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.4, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_3x3) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = -1.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = -1.0;
  A.matrix[1][1] = 2.0;
  A.matrix[1][2] = -1.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = -1.0;
  A.matrix[2][2] = 2.0;

  // Вычисляем обратную матрицу
  int inverse_result = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(inverse_result, OK);

  // Проверяем правильность значений
  ck_assert_double_eq_tol(result.matrix[0][0], 0.75, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.25, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 0.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], 0.25, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], 0.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 0.75, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_singular_matrix) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  // Заполняем сингулярную матрицу A (определитель = 0)
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  // Пытаемся вычислить обратную матрицу
  int inverse_result = s21_inverse_matrix(&A, &result);

  // Ожидаем ошибку, так как обратная матрица не существует (определитель = 0)
  ck_assert_int_eq(inverse_result, CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_incorrect_matrix) {
  matrix_t A, result;
  s21_create_matrix(3, 2, &A);  // Неквадратная матрица

  // Заполняем матрицу A
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;

  // Пытаемся вычислить обратную матрицу
  int inverse_result = s21_inverse_matrix(&A, &result);

  // Ожидаем ошибку, так как матрица неквадратная
  ck_assert_int_eq(inverse_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 4.0;

  // Вычисляем обратную матрицу
  int inverse_result = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(inverse_result, OK);

  // Проверяем правильность значений (обратная для 1x1 - это 1/элемент)
  ck_assert_double_eq_tol(result.matrix[0][0], 0.25, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_1) {
  matrix_t A = {0}, result, check = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  A.matrix[0][0] = 2, A.matrix[0][1] = 5, A.matrix[0][2] = 7;
  A.matrix[1][0] = 6, A.matrix[1][1] = 3, A.matrix[1][2] = 4;
  A.matrix[2][0] = 5, A.matrix[2][1] = -2, A.matrix[2][2] = -3;

  check.matrix[0][0] = 1, check.matrix[0][1] = -1, check.matrix[0][2] = 1;
  check.matrix[1][0] = -38, check.matrix[1][1] = 41, check.matrix[1][2] = -34;
  check.matrix[2][0] = 27, check.matrix[2][1] = -29, check.matrix[2][2] = 24;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_s21_inverse_matrix_2) {
  matrix_t A = {0}, result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 3, A.matrix[0][1] = 2, A.matrix[0][2] = 2;
  A.matrix[1][0] = 2, A.matrix[1][1] = 2, A.matrix[1][2] = 8;
  A.matrix[2][0] = 3, A.matrix[2][1] = 2, A.matrix[2][2] = 2;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_3) {
  matrix_t A = {0}, result, check = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  check.matrix[0][0] = 1.0, check.matrix[0][1] = -1.0, check.matrix[0][2] = 1.0;
  check.matrix[1][0] = -38.0, check.matrix[1][1] = 41.0,
  check.matrix[1][2] = -34.0;
  check.matrix[2][0] = 27.0, check.matrix[2][1] = -29.0,
  check.matrix[2][2] = 24.0;

  A.matrix[0][0] = 2.0, A.matrix[0][1] = 5.0, A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0, A.matrix[1][1] = 3.0, A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0, A.matrix[2][1] = -2.0, A.matrix[2][2] = -3.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

Suite *test_inverse_matrix(void) {
  Suite *s = suite_create("\033[35ms21_inverse_matrix\033[0m");
  TCase *tc_core = tcase_create("inverse_matrix_tc");

  // Добавляем тесты для функции s21_inverse_matrix
  tcase_add_test(tc_core, test_s21_inverse_matrix_2x2);
  tcase_add_test(tc_core, test_s21_inverse_matrix_3x3);
  tcase_add_test(tc_core, test_s21_inverse_matrix_singular_matrix);
  tcase_add_test(tc_core, test_s21_inverse_matrix_1);
  tcase_add_test(tc_core, test_s21_inverse_matrix_2);
  tcase_add_test(tc_core, test_s21_inverse_matrix_3);
  tcase_add_test(tc_core, test_s21_inverse_matrix_incorrect_matrix);
  tcase_add_test(tc_core, test_s21_inverse_matrix_1x1);

  suite_add_tcase(s, tc_core);

  return s;
}