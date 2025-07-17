#include "test_decimal.h"

// Тест на преобразование положительного числа
START_TEST(test_from_int_to_decimal_positive) {
  int src = 123456;
  s21_decimal expected = {{123456, 0, 0, 0}};  // 123456
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование отрицательного числа
START_TEST(test_from_int_to_decimal_negative) {
  int src = -654321;
  s21_decimal expected = {{654321, 0, 0, 0x80000000}};  // -654321
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование нуля
START_TEST(test_from_int_to_decimal_zero) {
  int src = 0;
  s21_decimal expected = {{0, 0, 0, 0}};  // 0
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование минимального значения int
START_TEST(test_from_int_to_decimal_min) {
  int src = -2147483648;
  s21_decimal expected = {{-2147483648, 0, 0, -2147483648}};  // -2147483648
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование максимального значения int
START_TEST(test_from_int_to_decimal_max) {
  int src = 2147483647;
  s21_decimal expected = {{2147483647, 0, 0, 0}};  // 2147483647
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование небольшого отрицательного числа
START_TEST(test_from_int_to_decimal_small_negative) {
  int src = -1;
  s21_decimal expected = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование числа в пределах значений short int
START_TEST(test_from_int_to_decimal_short_int) {
  int src = 32767;
  s21_decimal expected = {{32767, 0, 0, 0}};  // 32767
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование небольшого положительного числа
START_TEST(test_from_int_to_decimal_small_positive) {
  int src = 1;
  s21_decimal expected = {{1, 0, 0, 0}};  // 1
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование отрицательного числа в пределах значений short int
START_TEST(test_from_int_to_decimal_short_int_negative) {
  int src = -32768;
  s21_decimal expected = {{32768, 0, 0, 0x80000000}};  // -32768
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование числа 1000000
START_TEST(test_from_int_to_decimal_large_positive) {
  int src = 1000000;
  s21_decimal expected = {{1000000, 0, 0, 0}};  // 1000000
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_verter1) {
  int src = 10;
  s21_decimal expected = {{10, 0, 0, 0}};  // 1000000
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_verter2) {
  int src = -133546435;
  s21_decimal expected = {{133546435, 0, 0, -2147483648}};  // 1000000
  s21_decimal result;
  int error_code = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Создание тестового набора
Suite *test_from_int_to_decimal(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[35ms21_from_int_to_decimal\033[0m");

  tc_core = tcase_create("from_int_to_decimal_tc");

  tcase_add_test(tc_core, test_from_int_to_decimal_positive);
  tcase_add_test(tc_core, test_from_int_to_decimal_negative);
  tcase_add_test(tc_core, test_from_int_to_decimal_zero);
  tcase_add_test(tc_core, test_from_int_to_decimal_min);
  tcase_add_test(tc_core, test_from_int_to_decimal_max);
  tcase_add_test(tc_core, test_from_int_to_decimal_small_negative);
  tcase_add_test(tc_core, test_from_int_to_decimal_short_int);
  tcase_add_test(tc_core, test_from_int_to_decimal_small_positive);
  tcase_add_test(tc_core, test_from_int_to_decimal_short_int_negative);
  tcase_add_test(tc_core, test_from_int_to_decimal_large_positive);
  tcase_add_test(tc_core, test_verter1);
  tcase_add_test(tc_core, test_verter2);

  suite_add_tcase(s, tc_core);

  return s;
}
