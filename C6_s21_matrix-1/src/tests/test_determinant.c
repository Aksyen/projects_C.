#include "test_matrix.h"

START_TEST(test_s21_determinant_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 5.0;

  double result = 0.0;
  int determinant_result = s21_determinant(&A, &result);

  ck_assert_int_eq(determinant_result, OK);
  ck_assert_double_eq(
      result, 5.0);  // Определитель 1x1 матрицы - это единственный элемент

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_2x2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  // Заполняем матрицу A
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  double result = 0.0;
  int determinant_result = s21_determinant(&A, &result);

  ck_assert_int_eq(determinant_result, OK);
  ck_assert_double_eq(result, -2.0);  // det(A) = 1*4 - 2*3 = -2

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_3x3) {
  matrix_t A;
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

  double result = 0.0;
  int determinant_result = s21_determinant(&A, &result);

  ck_assert_int_eq(determinant_result, OK);

  ck_assert_double_eq(result, 22.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_singular_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  // Заполняем матрицу A (сингулярная матрица, определитель = 0)
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  double result = 0.0;
  int determinant_result = s21_determinant(&A, &result);

  ck_assert_int_eq(determinant_result, OK);
  ck_assert_double_eq(result, 0.0);  // det(A) = 0 (сингулярная матрица)

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_incorrect_matrix) {
  matrix_t A;
  s21_create_matrix(3, 2,
                    &A);  // Неквадратная матрица (определитель не существует)

  double result = 0.0;
  int determinant_result = s21_determinant(&A, &result);

  ck_assert_int_eq(determinant_result, INCORRECT_MATRIX);  // Ожидаем ошибку

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_3x3_2) {
  matrix_t A = {0};
  double res = 0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1, A.matrix[0][1] = -2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 4, A.matrix[1][1] = 0, A.matrix[1][2] = 6;
  A.matrix[2][0] = -7, A.matrix[2][1] = 8, A.matrix[2][2] = 9;
  ck_assert_int_eq(OK, s21_determinant(&A, &res));
  ck_assert_double_eq(204, res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_4x4) {
  matrix_t A = {0};
  double res = 0;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 3, A.matrix[0][1] = -3, A.matrix[0][2] = -5,
  A.matrix[0][3] = 8;
  A.matrix[1][0] = -3, A.matrix[1][1] = 2, A.matrix[1][2] = 4,
  A.matrix[1][3] = -6;
  A.matrix[2][0] = 2, A.matrix[2][1] = -5, A.matrix[2][2] = -7,
  A.matrix[2][3] = 5;
  A.matrix[3][0] = -4, A.matrix[3][1] = 3, A.matrix[3][2] = 5,
  A.matrix[3][3] = -6;
  ck_assert_int_eq(OK, s21_determinant(&A, &res));
  ck_assert_double_eq(18, res);
  s21_remove_matrix(&A);
}
END_TEST

Suite *test_determinant(void) {
  Suite *s = suite_create("\033[35ms21_determinant\033[0m");
  TCase *tc_core = tcase_create("determinant_tc");

  // Добавляем тесты для функции s21_determinant
  tcase_add_test(tc_core, test_s21_determinant_1x1);
  tcase_add_test(tc_core, test_s21_determinant_2x2);
  tcase_add_test(tc_core, test_s21_determinant_3x3);
  tcase_add_test(tc_core, test_s21_determinant_3x3_2);
  tcase_add_test(tc_core, test_s21_determinant_4x4);
  tcase_add_test(tc_core, test_s21_determinant_singular_matrix);
  tcase_add_test(tc_core, test_s21_determinant_incorrect_matrix);

  suite_add_tcase(s, tc_core);

  return s;
}