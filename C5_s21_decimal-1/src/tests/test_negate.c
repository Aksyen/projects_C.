#include "test_decimal.h"

START_TEST(test_negate_positive_to_negative) {
  s21_decimal value = {{123, 0, 0, 0x00000000}};  // Положительное число
  s21_decimal expected = {
      {123, 0, 0, 0x80000000}};  // Ожидаемое отрицательное число
  s21_decimal result;

  int error_code = s21_negate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  s21_decimal value2 = {{1, 1, 1, 917504}};          // 184467.44078004518913
  s21_decimal expected2 = {{1, 1, 1, -2146566144}};  // -184467.44078004518913
  s21_decimal result2;

  int error_code2 = s21_negate(value2, &result2);

  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_negate_negative_to_positive) {
  s21_decimal value = {{123, 0, 0, 0x80000000}};  // Отрицательное число
  s21_decimal expected = {
      {123, 0, 0, 0x00000000}};  // Ожидаемое положительное число
  s21_decimal result;

  int error_code = s21_negate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  s21_decimal value2 = {
      {32444, 100, 343253, -2145976320}};  // -63.31900243533454217608892
  s21_decimal expected2 = {
      {32444, 100, 343253, 1507328}};  // 63.31900243533454217608892
  s21_decimal result2;

  int error_code2 = s21_negate(value2, &result2);

  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_negate_zero_positive) {
  s21_decimal value = {{0, 0, 0, 917504}};  // Положительный ноль
  s21_decimal expected = {
      {0, 0, 0, -2146566144}};  // Ожидаемый отрицательный ноль
  s21_decimal result;

  int error_code = s21_negate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_negate_zero_negative) {
  s21_decimal value = {{0, 0, 0, 0x80000000}};  // Отрицательный ноль
  s21_decimal expected = {
      {0, 0, 0, 0x00000000}};  // Ожидаемый положительный ноль
  s21_decimal result;

  int error_code = s21_negate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_negate_null_pointer) {
  s21_decimal value = {{123, 0, 0, 0x00000000}};  // Любое число

  int error_code =
      s21_negate(value, NULL);  // Передаем NULL как указатель на результат

  ck_assert_int_eq(error_code, 1);  // Ожидаем код ошибки 1
}
END_TEST

Suite *test_negate(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[35ms21_negate\033[0m");

  tc_core = tcase_create("negate_tc");

  tcase_add_test(tc_core, test_negate_positive_to_negative);
  tcase_add_test(tc_core, test_negate_negative_to_positive);
  tcase_add_test(tc_core, test_negate_zero_positive);
  tcase_add_test(tc_core, test_negate_zero_negative);
  tcase_add_test(tc_core, test_negate_null_pointer);

  suite_add_tcase(s, tc_core);

  return s;
}