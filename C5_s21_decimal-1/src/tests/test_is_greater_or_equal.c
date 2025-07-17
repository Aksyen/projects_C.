#include "test_decimal.h"

START_TEST(is_greater_or_equal_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal val1 = {{1, 2, 3, 655360}};
  s21_decimal val2 = {{3, 2, 1, -2146828288}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal val1 = {{1, 2, 3, -2146828288}};
  s21_decimal val2 = {{3, 2, 1, -2146828288}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal val1 = {{1, 2, 3, -2146566144}};
  s21_decimal val2 = {{3, 2, 1, -2146959360}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal val1 = {{10, 2, 3, -2146566144}};
  s21_decimal val2 = {{3, 2, 1, 524288}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal val1 = {{1, 2, 3, 917504}};
  s21_decimal val2 = {{1, 2, 3, 917504}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

Suite *test_is_greater_or_equal(void) {
  Suite *s = suite_create("\033[35ms21_is_greater_or_equal\033[0m");
  TCase *tc = tcase_create("is_greater_or_equal_tc");

  tcase_add_test(tc, is_greater_or_equal_0);
  tcase_add_test(tc, is_greater_or_equal_1);
  tcase_add_test(tc, is_greater_or_equal_2);
  tcase_add_test(tc, is_greater_or_equal_3);
  tcase_add_test(tc, is_greater_or_equal_4);
  tcase_add_test(tc, is_greater_or_equal_5);
  // tcase_add_test(tc, is_greater_1);
  // tcase_add_test(tc, is_greater_2);
  // tcase_add_test(tc, is_greater_3);
  // tcase_add_test(tc, is_greater_4);
  // tcase_add_test(tc, is_greater_5);
  // tcase_add_test(tc, is_greater_6);
  // tcase_add_test(tc, is_greater_7);
  // tcase_add_test(tc, is_greater_8);
  // tcase_add_test(tc, mul_9);
  // tcase_add_test(tc, mul_10);
  // tcase_add_test(tc, mul_11);
  //   tcase_add_test(tc, mul_12);
  //  tcase_add_test(tc, mul_13);
  //  tcase_add_test(tc, mul_14);
  // tcase_add_test(tc, div_15);
  // tcase_add_test(tc, div_16);
  // tcase_add_test(tc, div_17);
  // tcase_add_test(tc, div_18);
  // tcase_add_test(tc, div_19);

  suite_add_tcase(s, tc);
  return s;
}
