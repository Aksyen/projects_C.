#include "test_matrix.h"

START_TEST(test_s21_eq_matrix_equal) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Заполняем обе матрицы одинаковыми значениями
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
    }
  }

  int result = s21_eq_matrix(&A, &B);
  // Ожидаем успех, так как матрицы идентичны
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_not_equal_size) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 3, &B);  // Создаем матрицу другого размера

  int result = s21_eq_matrix(&A, &B);
  // Ожидаем неудачу, так как размеры матриц не совпадают
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_not_equal_values) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Заполняем матрицы разными значениями
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j + 1;  // Отличие в значении
    }
  }

  int result = s21_eq_matrix(&A, &B);
  // Ожидаем неудачу, так как элементы матриц различаются
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_almost_equal) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Заполняем матрицы почти одинаковыми значениями
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j + 1e-8;  // Небольшое отличие в значении
    }
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);  // Ожидаем успех, так как разница в
                                      // пределах допустимой погрешности

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_null_pointers) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Тесты на случай передачи NULL указателей
  int result = s21_eq_matrix(NULL, &B);
  // Ожидаем неудачу, так как один из указателей равен NULL
  ck_assert_int_eq(result, FAILURE);

  result = s21_eq_matrix(&A, NULL);
  // Ожидаем неудачу, так как один из указателей равен NULL
  ck_assert_int_eq(result, FAILURE);

  result = s21_eq_matrix(NULL, NULL);
  // Ожидаем неудачу, так как оба указателя равны NULL
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *test_eq_matrix(void) {
  Suite *s = suite_create("\033[35ms21_eq_matrix\033[0m");
  TCase *tc_core = tcase_create("eq_matrix_tc");

  // Добавляем тесты в тестовый случай
  tcase_add_test(tc_core, test_s21_eq_matrix_equal);
  tcase_add_test(tc_core, test_s21_eq_matrix_not_equal_size);
  tcase_add_test(tc_core, test_s21_eq_matrix_not_equal_values);
  tcase_add_test(tc_core, test_s21_eq_matrix_almost_equal);
  tcase_add_test(tc_core, test_s21_eq_matrix_null_pointers);

  suite_add_tcase(s, tc_core);

  return s;
}