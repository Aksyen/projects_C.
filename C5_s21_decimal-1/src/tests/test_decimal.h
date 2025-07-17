#ifndef S21_TEST_DECIMAL_H
#define S21_TEST_DECIMAL_H

// #define STRLEN 128

#include <check.h>
#include <limits.h>
#include <stdio.h>
// #include <string.h>

#include "../s21_decimal.h"

Suite *test_add(void);
Suite *test_sub(void);
Suite *test_div(void);
Suite *test_mul(void);

Suite *test_is_greater(void);
Suite *test_is_greater_or_equal(void);
Suite *test_is_less(void);
Suite *test_is_less_or_equal(void);
Suite *test_is_equal(void);
Suite *test_is_not_equal(void);

Suite *test_negate(void);
Suite *test_truncate(void);
Suite *test_round(void);
Suite *test_floor(void);

Suite *test_from_int_to_decimal(void);
Suite *test_from_decimal_to_int(void);
Suite *test_from_float_to_decimal(void);
Suite *test_from_decimal_to_float(void);

#endif  // S21_TEST_DECIMAL_H
