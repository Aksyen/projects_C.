#include "test_matrix.h"

START_TEST(test_s21_mult_matrix_valid) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  // Заполняем матрицу A значениями
  double counter = 1.0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = counter;
      counter += 1.0;
    }
  }

  // Заполняем матрицу B значениями
  counter = 1.0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      B.matrix[i][j] = counter;
      counter += 1.0;
    }
  }

  // Выполняем умножение
  int mult_result = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(mult_result, OK);

  // Ожидаемая матрица результата:
  // [ 22  28 ]
  // [ 49  64 ]
  ck_assert_double_eq(result.matrix[0][0], 22.0);
  ck_assert_double_eq(result.matrix[0][1], 28.0);
  ck_assert_double_eq(result.matrix[1][0], 49.0);
  ck_assert_double_eq(result.matrix[1][1], 64.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix_valid_non_square) {
  matrix_t A, B, result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);

  // Заполняем матрицу A значениями
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;

  // Заполняем матрицу B значениями
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[0][2] = 3.0;
  B.matrix[1][0] = 4.0;
  B.matrix[1][1] = 5.0;
  B.matrix[1][2] = 6.0;

  // Выполняем умножение
  int mult_result = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(mult_result, OK);

  // Проверяем размер результирующей матрицы
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  // Проверяем правильность значений
  ck_assert_double_eq(result.matrix[0][0], 9.0);
  ck_assert_double_eq(result.matrix[0][1], 12.0);
  ck_assert_double_eq(result.matrix[0][2], 15.0);
  ck_assert_double_eq(result.matrix[1][0], 19.0);
  ck_assert_double_eq(result.matrix[1][1], 26.0);
  ck_assert_double_eq(result.matrix[1][2], 33.0);
  ck_assert_double_eq(result.matrix[2][0], 29.0);
  ck_assert_double_eq(result.matrix[2][1], 40.0);
  ck_assert_double_eq(result.matrix[2][2], 51.0);

  // Очищаем матрицы
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix_invalid_size) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);  // Матрицы с несоответствующими размерами

  // Заполняем матрицы значениями
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = 1.0;
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      B.matrix[i][j] = 1.0;
    }
  }

  // Ожидаем ошибку из-за несоответствующих размеров
  int mult_result = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_null_pointer) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // Заполняем матрицы значениями
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = 1.0;
      B.matrix[i][j] = 2.0;
    }
  }

  // Проверка с NULL указателями
  int mult_result = s21_mult_matrix(NULL, &B, &result);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  mult_result = s21_mult_matrix(&A, NULL, &result);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  mult_result = s21_mult_matrix(&A, &B, NULL);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_overflow) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // Заполняем матрицы значениями, которые могут привести к переполнению
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = DBL_MAX / 2;  // Значение близкое к пределу
      B.matrix[i][j] = 2.0;
    }
  }

  // Умножаем матрицы, что приведет к переполнению
  int mult_result = s21_mult_matrix(&A, &B, &result);
  // Ожидаем ошибку переполнения
  ck_assert_int_eq(mult_result, CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_plus) {
  matrix_t A = {0}, B = {0}, check = {0}, res;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &check);

  A.matrix[0][0] = 1.2, A.matrix[0][1] = 2.4;
  A.matrix[1][0] = 3.6, A.matrix[1][1] = 4.8;
  A.matrix[2][0] = 6.0, A.matrix[2][1] = 7.2;

  B.matrix[0][0] = 3.5, B.matrix[0][1] = 7.0, B.matrix[0][2] = 10.5;
  B.matrix[1][0] = 14.0, B.matrix[1][1] = 17.5, B.matrix[1][2] = 21.0;

  check.matrix[0][0] = 37.8, check.matrix[0][1] = 50.4, check.matrix[0][2] = 63;
  check.matrix[1][0] = 79.8, check.matrix[1][1] = 109.2,
  check.matrix[1][2] = 138.6;
  check.matrix[2][0] = 121.8, check.matrix[2][1] = 168,
  check.matrix[2][2] = 214.2;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&res);
}
END_TEST

Suite *test_mult_matrix(void) {
  Suite *s = suite_create("\033[35ms21_mult_matrix\033[0m");
  TCase *tc_core = tcase_create("mult_matrix_tc");

  // Добавляем тесты в тестовый случай
  tcase_add_test(tc_core, test_s21_mult_matrix_valid);
  tcase_add_test(tc_core, test_s21_mult_matrix_valid_non_square);
  tcase_add_test(tc_core, test_s21_mult_matrix_invalid_size);
  tcase_add_test(tc_core, test_s21_mult_matrix_null_pointer);
  tcase_add_test(tc_core, test_s21_mult_matrix_overflow);
  tcase_add_test(tc_core, test_s21_mult_matrix_plus);

  suite_add_tcase(s, tc_core);

  return s;
}
