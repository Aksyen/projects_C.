#include "test_decimal.h"

// Тест на преобразование положительного числа
START_TEST(test_from_decimal_to_int_positive) {
  s21_decimal src = {{123456, 0, 0, 0}};  // 123456
  int expected = 123456;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование отрицательного числа
START_TEST(test_from_decimal_to_int_negative) {
  s21_decimal src = {{654321, 0, 0, 0x80000000}};  // -654321
  int expected = -654321;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование нуля
START_TEST(test_from_decimal_to_int_zero) {
  s21_decimal src = {{0, 0, 0, 0}};  // 0
  int expected = 0;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование минимального значения int
START_TEST(test_from_decimal_to_int_min) {
  s21_decimal src = {{-2147483648, 0, 0, -2147483648}};  // -2147483648
  int expected = -2147483648;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование максимального значения int
START_TEST(test_from_decimal_to_int_max) {
  s21_decimal src = {{2147483647, 0, 0, 0}};  // 2147483647
  int expected = 2147483647;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование небольшого отрицательного числа
START_TEST(test_from_decimal_to_int_small_negative) {
  s21_decimal src = {{1, 0, 0, 0x80000000}};  // -1
  int expected = -1;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование числа в пределах значений short int
START_TEST(test_from_decimal_to_int_short_int) {
  s21_decimal src = {{32767, 0, 0, 0}};  // 32767
  int expected = 32767;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование небольшого положительного числа
START_TEST(test_from_decimal_to_int_small_positive) {
  s21_decimal src = {{1, 0, 0, 0}};  // 1
  int expected = 1;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование отрицательного числа в пределах значений short int
START_TEST(test_from_decimal_to_int_short_int_negative) {
  s21_decimal src = {{32768, 0, 0, 0x80000000}};  // -32768
  int expected = -32768;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на преобразование числа 1000000
START_TEST(test_from_decimal_to_int_large_positive) {
  s21_decimal src = {{1000000, 0, 0, 0}};  // 1000000
  int expected = 1000000;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Тест на переполнение положительного значения
START_TEST(test_from_decimal_to_int_overflow_positive) {
  s21_decimal src = {
      {-2147483648, 0, 0, 0}};  // 2147483648 (выход за пределы int)
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 1);  // Ожидается ошибка переполнения
}
END_TEST

// Тест на переполнение отрицательного значения
START_TEST(test_from_decimal_to_int_overflow_negative) {
  s21_decimal src = {
      {-2147483647, 0, 0, -2147483648}};  // -2147483649 (выход за пределы int)
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 1);  // Ожидается ошибка переполнения
}
END_TEST

START_TEST(verter1) {
  s21_decimal src = {{10, 0, 0, 0}};  // 1000000
  int expected = 10;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(verter2) {
  s21_decimal src = {{133546435, 0, 0, -2147483648}};  // 1000000
  int expected = -133546435;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

// Создание тестового набора
Suite *test_from_decimal_to_int(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[35ms21_from_decimal_to_int\033[0m");

  tc_core = tcase_create("from_decimal_to_int_tc");

  tcase_add_test(tc_core, test_from_decimal_to_int_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_negative);
  tcase_add_test(tc_core, test_from_decimal_to_int_zero);
  tcase_add_test(tc_core, test_from_decimal_to_int_min);
  tcase_add_test(tc_core, test_from_decimal_to_int_max);
  tcase_add_test(tc_core, test_from_decimal_to_int_small_negative);
  tcase_add_test(tc_core, test_from_decimal_to_int_short_int);
  tcase_add_test(tc_core, test_from_decimal_to_int_small_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_short_int_negative);
  tcase_add_test(tc_core, test_from_decimal_to_int_large_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_overflow_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_overflow_negative);
  tcase_add_test(tc_core, verter1);
  tcase_add_test(tc_core, verter2);

  suite_add_tcase(s, tc_core);

  return s;
}
