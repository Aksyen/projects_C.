#include "test_decimal.h"

// Тест на преобразование положительного числа
START_TEST(test_from_decimal_to_float_verter_val1) {
  s21_decimal val = {{2343453, 0, 0, -2147024896}};
  float expected = -0.2343453;
  float result = 0;
  int error_code = s21_from_decimal_to_float(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST
START_TEST(test_from_decimal_to_float_verter_val2) {
  s21_decimal val = {{1272343, 0, 0, 262144}};
  float expected = 127.2343;
  float result = 0;
  int error_code = s21_from_decimal_to_float(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование положительного числа
START_TEST(test_from_decimal_to_float_positive) {
  s21_decimal src = {{23434530, 0, 0, 65536}};  // 2343453.0
  float expected = 2343453.0f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование отрицательного числа
START_TEST(test_from_decimal_to_float_negative) {
  s21_decimal src = {{23434530, 0, 0, -2147418112}};  // -2343453.0
  float expected = -2343453.0f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование числа с дробной частью
START_TEST(test_from_decimal_to_float_fractional) {
  s21_decimal src = {{123456, 0, 0, 393216}};  // 0.123456
  float expected = 0.123456f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование отрицательного числа с дробной частью
START_TEST(test_from_decimal_to_float_negative_fractional) {
  s21_decimal src = {{123456, 0, 0, -2147090432}};  // -0.123456
  float expected = -0.123456f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование большого положительного числа
START_TEST(test_from_decimal_to_float_large_positive) {
  s21_decimal src = {{-10, 9, 0, 65536}};  // 4294967295.0
  float expected = 4294967295.0f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование маленького положительного числа
START_TEST(test_from_decimal_to_float_small_positive) {
  s21_decimal src = {{1, 0, 0, 393216}};  // 0.000001
  float expected = 0.000001f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование очень маленького отрицательного числа
START_TEST(test_from_decimal_to_float_very_small_negative) {
  s21_decimal src = {{10, 0, 0, -2146762752}};  // -1.0e-10
  float expected = -1.0e-10f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование очень большого отрицательного числа
START_TEST(test_from_decimal_to_float_very_large_negative) {
  s21_decimal src = {{-10, 9, 0, -2147418112}};  // -4294967295.0
  float expected = -4294967295.0f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на преобразование числа 1.5
START_TEST(test_from_decimal_to_float_one_point_five) {
  s21_decimal src = {{15, 0, 0, 65536}};  // 1.5
  float expected = 1.5f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Тест на 0
START_TEST(test_from_decimal_to_float_zero) {
  s21_decimal src = {{0, 0, 0, 0}};
  float expected = 0.0f;
  float result = 0.0f;
  int error_code = s21_from_decimal_to_float(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_float_eq(result, expected);
}
END_TEST

// Создание тестового набора
Suite *test_from_decimal_to_float(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[35ms21_from_decimal_to_float\033[0m");

  tc_core = tcase_create("from_from_decimal_to_float_tc");

  tcase_add_test(tc_core, test_from_decimal_to_float_verter_val1);
  tcase_add_test(tc_core, test_from_decimal_to_float_verter_val2);
  tcase_add_test(tc_core, test_from_decimal_to_float_positive);
  tcase_add_test(tc_core, test_from_decimal_to_float_negative);
  tcase_add_test(tc_core, test_from_decimal_to_float_fractional);
  tcase_add_test(tc_core, test_from_decimal_to_float_negative_fractional);
  tcase_add_test(tc_core, test_from_decimal_to_float_large_positive);
  tcase_add_test(tc_core, test_from_decimal_to_float_small_positive);
  tcase_add_test(tc_core, test_from_decimal_to_float_very_small_negative);
  tcase_add_test(tc_core, test_from_decimal_to_float_very_large_negative);
  tcase_add_test(tc_core, test_from_decimal_to_float_one_point_five);
  tcase_add_test(tc_core, test_from_decimal_to_float_zero);

  suite_add_tcase(s, tc_core);

  return s;
}