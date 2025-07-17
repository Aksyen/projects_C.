#include "test_decimal.h"

START_TEST(test_round_positive_no_fraction) {
  s21_decimal value = {{1, 2, 3, 917504}};     // 553402.32229718589441
  s21_decimal expected = {{553402, 0, 0, 0}};  // 553402
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  s21_decimal value2 = {{16, 100, 3, 851968}};   // 5534023.2650625384464
  s21_decimal expected2 = {{5534023, 0, 0, 0}};  // 5534023
  s21_decimal result2;
  int error_code2 = s21_round(value2, &result2);
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));

  s21_decimal value3 = {{2112827408, 798, 3, 851968}};  // 5534023.5650625384464
  s21_decimal expected3 = {{5534024, 0, 0, 0}};         // 5534024
  s21_decimal result3;
  int error_code3 = s21_round(value3, &result3);
  ck_assert_int_eq(error_code3, 0);
  ck_assert_mem_eq(&result3, &expected3, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_negative_no_fraction) {
  s21_decimal value = {
      {-1662697471, 4658, 3, -2146566144}};  // -553402.52229718589441
  s21_decimal expected = {{553403, 0, 0, -2147483648}};  // -553403
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  s21_decimal value2 = {{16, 100, 3, -2146631680}};  // -5534023.2650625384464
  s21_decimal expected2 = {{5534023, 0, 0, -2147483648}};  // 5534023
  s21_decimal result2;
  int error_code2 = s21_round(value2, &result2);
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_positive_fraction_half) {
  s21_decimal value = {{25, 30, 0, 65536}};  // 12884901890.5
  s21_decimal expected = {{3, 3, 0, 0}};     // 12884901891
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  s21_decimal value2 = {{3, 3, 0, 0}};     // 12884901891
  s21_decimal expected2 = {{3, 3, 0, 0}};  // 12884901891
  s21_decimal result2;
  int error_code2 = s21_round(value2, &result2);
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_positive_fraction_less_half) {
  s21_decimal value = {{225, 300, 0, 131072}};  // 12884901890.25
  s21_decimal expected = {{2, 3, 0, 0}};        // 12884901890
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_negative_fraction_half) {
  s21_decimal value = {
      {792095801, -1320247423, 6, -2147418112}};  // -12345678901234567890.5
  s21_decimal expected = {
      {-350287149, -1420514932, 0, -2147483648}};  // -12345678901234567891
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_zero) {
  s21_decimal value = {{25, 0, 0, 131072}};  // 0.25
  s21_decimal expected = {{0, 0, 0, 0}};     // 0
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));

  s21_decimal value2 = {{10, 100, 3, 1376256}};  // 0.055340232650625384458
  s21_decimal expected2 = {{0, 0, 0, 0}};        // 0
  s21_decimal result2;
  int error_code2 = s21_round(value2, &result2);
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_small_fraction_positive) {
  s21_decimal value = {{10625, 10000, 0, 262144}};  // 4294967297.0625
  s21_decimal expected = {{1, 1, 0, 0}};            // 4294967297
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_small_fraction_negative) {
  s21_decimal value = {{10625, 100000, 0, -2147221504}};  // -42949672961.0625
  s21_decimal expected = {{1, 10, 0, -2147483648}};       // -42949672961
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_positive_exact_half) {
  s21_decimal value = {{15, 10, 0, 65536}};  // 4294967297.5
  s21_decimal expected = {{2, 1, 0, 0}};     // 4294967298
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_round_negative_exact_half) {
  s21_decimal value = {{15, 10, 0, -2147418112}};   // -4294967297.5
  s21_decimal expected = {{2, 1, 0, -2147483648}};  // -4294967298
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

Suite *test_round(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[35ms21_round\033[0m");

  tc_core = tcase_create("round_tc");

  tcase_add_test(tc_core, test_round_positive_no_fraction);
  tcase_add_test(tc_core, test_round_negative_no_fraction);
  tcase_add_test(tc_core, test_round_positive_fraction_half);
  tcase_add_test(tc_core, test_round_positive_fraction_less_half);
  tcase_add_test(tc_core, test_round_negative_fraction_half);
  tcase_add_test(tc_core, test_round_zero);
  tcase_add_test(tc_core, test_round_small_fraction_positive);
  tcase_add_test(tc_core, test_round_small_fraction_negative);
  tcase_add_test(tc_core, test_round_positive_exact_half);
  tcase_add_test(tc_core, test_round_negative_exact_half);

  suite_add_tcase(s, tc_core);

  return s;
}