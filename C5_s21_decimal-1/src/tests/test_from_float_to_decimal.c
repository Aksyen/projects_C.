#include "test_decimal.h"

// Тест на преобразование положительного числа
START_TEST(test_from_float_verter_val1) {
  s21_decimal expected = {{2343453, 0, 0, -2147024896}};
  float val = -0.2343453;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST
START_TEST(test_from_float_verter_val2) {
  s21_decimal expected = {{1272343, 0, 0, 262144}};
  float val = 127.2343;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование положительного числа
START_TEST(test_from_float_to_decimal_positive) {
  s21_decimal expected = {{2343453, 0, 0, 0}};
  float val = 2343453.0;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование отрицательного числа
START_TEST(test_from_float_to_decimal_negative) {
  s21_decimal expected = {{2343453, 0, 0, -2147483648}};
  float val = -2343453.0;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование очень маленького числа
START_TEST(test_from_float_to_decimal_small_positive) {
  s21_decimal expected = {{1, 0, 0, 393216}};
  float val = 0.000001;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование числа с дробной частью
START_TEST(test_from_float_to_decimal_fractional) {
  s21_decimal expected = {{123456, 0, 0, 393216}};
  float val = 0.123456;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование отрицательного числа с дробной частью
START_TEST(test_from_float_to_decimal_negative_fractional) {
  s21_decimal expected = {{123456, 0, 0, -2147090432}};
  float val = -0.123456;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование числа 1.5
START_TEST(test_from_float_to_decimal_one_point_five) {
  s21_decimal expected = {{15, 0, 0, 65536}};
  float val = 1.5;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование очень маленького отрицательного числа
START_TEST(test_from_float_to_decimal_very_small_negative) {
  s21_decimal expected = {{1, 0, 0, -2146828288}};
  float val = -1.0e-10;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// Тест на преобразование положительного бесконечного значения float
START_TEST(test_from_float_to_decimal_infinity) {
  float val = 1.0f / 0.0f;  // inf
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 1);  // Ожидаем, что функция вернет ошибку
}
END_TEST

// Тест на преобразование отрицательного бесконечного значения float
START_TEST(test_from_float_to_decimal_negative_infinity) {
  float val = -1.0f / 0.0f;  // -inf
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 1);  // Ожидаем, что функция вернет ошибку
}
END_TEST

// Тест на преобразование значения NaN float
START_TEST(test_from_float_to_decimal_nan) {
  float val = 0.0f / 0.0f;  // NaN
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 1);  // Ожидаем, что функция вернет ошибку
}
END_TEST

// Создание тестового набора
Suite *test_from_float_to_decimal(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[35ms21_from_float_to_decimal\033[0m");

  tc_core = tcase_create("from_float_to_decimal_tc");

  tcase_add_test(tc_core, test_from_float_verter_val1);
  tcase_add_test(tc_core, test_from_float_verter_val2);
  tcase_add_test(tc_core, test_from_float_to_decimal_positive);
  tcase_add_test(tc_core, test_from_float_to_decimal_negative);
  tcase_add_test(tc_core, test_from_float_to_decimal_small_positive);
  tcase_add_test(tc_core, test_from_float_to_decimal_fractional);
  tcase_add_test(tc_core, test_from_float_to_decimal_negative_fractional);
  tcase_add_test(tc_core, test_from_float_to_decimal_one_point_five);
  tcase_add_test(tc_core, test_from_float_to_decimal_very_small_negative);
  tcase_add_test(tc_core, test_from_float_to_decimal_infinity);
  tcase_add_test(tc_core, test_from_float_to_decimal_negative_infinity);
  tcase_add_test(tc_core, test_from_float_to_decimal_nan);

  suite_add_tcase(s, tc_core);

  return s;
}
