#include "test_decimal.h"

START_TEST(is_greater_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal val1 = {{1, 2, 3, 655360}};
  s21_decimal val2 = {{3, 2, 1, -2146828288}};
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal val1 = {{1, 2, 3, -2146828288}};
  s21_decimal val2 = {{3, 2, 1, -2146828288}};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal val1 = {{1, 2, 3, -2146566144}};
  s21_decimal val2 = {{3, 2, 1, -2146959360}};
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal val1 = {{10, 2, 3, -2146566144}};
  s21_decimal val2 = {{3, 2, 1, 524288}};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal val1 = {{1, 2, 3, 917504}};
  s21_decimal val2 = {{1, 2, 3, 917504}};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

// START_TEST(is_greater_4) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   setBit(&val1, 127, 1);
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_5) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 11);
//   setScale(&val2, 10);
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_6) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val1.bits[0] = 257;
//   val2.bits[0] = 257;
//   val1.bits[2] = 256;
//   val2.bits[2] = 257;
//   setScale(&val1, 10);
//   setScale(&val2, 11);
//   ck_assert_int_eq(1, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_7) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val2.bits[2] = 257;
//   setBit(&val1, 127, 1);
//   setBit(&val2, 127, 1);
//   ck_assert_int_eq(1, s21_is_greater(val1, val2));
// }
// END_TEST

// START_TEST(is_greater_8) {
//   s21_decimal val1 = {0};
//   s21_decimal val2 = {0};
//   val2.bits[2] = 257;
//   setBit(&val1, 127, 1);
//   setBit(&val2, 127, 0);
//   ck_assert_int_eq(0, s21_is_greater(val1, val2));
// }
// END_TEST

Suite *test_is_greater(void) {
  Suite *s = suite_create("\033[35ms21_is_greater\033[0m");
  TCase *tc = tcase_create("is_greater_tc");

  tcase_add_test(tc, is_greater_0);
  tcase_add_test(tc, is_greater_1);
  tcase_add_test(tc, is_greater_2);
  tcase_add_test(tc, is_greater_3);
  tcase_add_test(tc, is_greater_4);
  tcase_add_test(tc, is_greater_5);
  tcase_add_test(tc, is_greater_6);
  tcase_add_test(tc, is_greater_7);
  tcase_add_test(tc, is_greater_8);
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
