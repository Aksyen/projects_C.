#include "test_decimal.h"

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  // DEC (0)
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  // DEC (0)
  s21_decimal val2 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  // DEC (0)
  s21_decimal correct = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_13) {
  // DEC (-1)
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  // DEC (-1)
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  // DEC (1)
  s21_decimal correct = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_14) {
  // DEC (-1.00)
  s21_decimal val1 = {
      {0b00000000000000000000000001100100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000100000000000000000}};
  // DEC (-1)
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  // DEC (1)
  s21_decimal correct = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_15) {
  // DEC (0.02)
  s21_decimal val1 = {
      {0b00000000000000000000000000000010, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000100000000000000000}};
  // DEC (-0.2)
  s21_decimal val2 = {
      {0b00000000000000000000000000000010, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000010000000000000000}};
  // DEC (-0.004)
  s21_decimal correct = {
      {0b00000000000000000000000000000100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000110000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_16) {
  // DEC (0.020)
  s21_decimal val1 = {
      {0b00000000000000000000000000010100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000110000000000000000}};
  // DEC (-0.2)
  s21_decimal val2 = {
      {0b00000000000000000000000000000010, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000010000000000000000}};
  // DEC (-0.004)
  s21_decimal correct = {
      {0b00000000000000000000000000000100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000110000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_17) {
  // DEC (333.3330)
  s21_decimal val1 = {
      {0b00000000001100101101110011010010, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001000000000000000000}};
  // DEC (-444.4440)
  s21_decimal val2 = {
      {0b00000000010000111101000100011000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000001000000000000000000}};
  // DEC (-148147,851852)
  s21_decimal correct = {
      {0b01111110010011001101001001001100, 0b00000000000000000000000000100010,
       0b00000000000000000000000000000000, 0b10000000000001100000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_18) {
  // DEC (1000000000000000.1)
  s21_decimal val1 = {
      {0b01101111110000010000000000000001, 0b00000000001000111000011011110010,
       0b00000000000000000000000000000000, 0b00000000000000010000000000000000}};
  // DEC (1000000000000000.1)
  s21_decimal val2 = {
      {0b01101111110000010000000000000001, 0b00000000001000111000011011110010,
       0b00000000000000000000000000000000, 0b00000000000000010000000000000000}};
  // DEC (0)
  s21_decimal correct = {
      {0b00000000000000000000000000000000, 0b0000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b0000000000000000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_19) {
  // DEC (1000000000000000.1)
  s21_decimal val1 = {
      {0b01101111110000010000000000000001, 0b00000000001000111000011011110010,
       0b00000000000000000000000000000000, 0b00000000000000010000000000000000}};
  // DEC (-1000000000000000.1)
  s21_decimal val2 = {
      {0b01101111110000010000000000000001, 0b00000000001000111000011011110010,
       0b00000000000000000000000000000000, 0b10000000000000010000000000000000}};
  // DEC (0)
  s21_decimal correct = {
      {0b00000000000000000000000000000000, 0b0000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b0000000000000000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_20) {
  // DEC (max/2)
  s21_decimal val1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b01111111111111111111111111111111, 0b00000000000000000000000000000000}};
  // DEC (-2)
  s21_decimal val2 = {
      {0b00000000000000000000000000000010, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  // DEC (- (max - 1) )
  s21_decimal correct = {
      {0b11111111111111111111111111111110, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_21) {
  // DEC (1 1 1 exp=10)
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b00000000000010100000000000000000}};
  // DEC (1 1 1 exp=10)
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b00000000000010100000000000000000}};
  // DEC (3402823670793947885.4724351485)
  s21_decimal correct = {
      {0b01100010100000011111010111111101, 0b00111010110111011110100110101111,
       0b01101101111100110111111101101000, 0b00000000000010100000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_22) {
  // DEC (1 exp=10)
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000010100000000000000000}};
  // DEC (1 exp=10)
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000010100000000000000000}};
  // DEC (0.00000000000000000001)
  s21_decimal correct = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000101000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_23) {
  // DEC (1 exp=10)
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000010100000000000000000}};
  // DEC (1 exp=10 -)
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000010100000000000000000}};
  // DEC (-0.00000000000000000001)
  s21_decimal correct = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000101000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_24) {
  // DEC (1 exp=10)
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000001, 0b00000000000011100000000000000000}};
  // DEC (1 exp=10 -)
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000010100000000000000000}};
  // DEC (-0.000018446744073709551617)
  s21_decimal correct = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000001, 0b10000000000110000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_25) {
  // DEC (0)
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  // DEC (1 exp=10 -)
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000010100000000000000000}};
  // DEC (-0)
  s21_decimal correct = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

Suite *test_mul(void) {
  Suite *s = suite_create("\033[35ms21_mul\033[0m");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, mul_0);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  tcase_add_test(tc, mul_15);
  tcase_add_test(tc, mul_16);
  tcase_add_test(tc, mul_17);
  tcase_add_test(tc, mul_18);
  tcase_add_test(tc, mul_19);
  tcase_add_test(tc, mul_20);
  tcase_add_test(tc, mul_21);
  tcase_add_test(tc, mul_22);
  tcase_add_test(tc, mul_23);
  tcase_add_test(tc, mul_24);
  tcase_add_test(tc, mul_25);

  suite_add_tcase(s, tc);
  return s;
}
