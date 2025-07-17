#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  const s21_w_dec zero = {{0, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec val1 = dec_to_wdec(value_1);
  s21_w_dec val2 = dec_to_wdec(value_2);
  int ret = 0, flag = 1;
  if ((!val1.sig && val2.sig) || (val1.sig && !val2.sig)) {
    flag = 0;
  }
  if (!compare(val1, zero) && !compare(val2, zero)) {
    flag = 0;
    ret = 1;
  }
  if (flag) {
    normaliz(&val1, &val2);
    if (!compare(val1, val2)) ret = 1;
  }
  return ret;
}