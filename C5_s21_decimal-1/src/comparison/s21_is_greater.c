#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_w_dec val1 = dec_to_wdec(value_1);
  s21_w_dec val2 = dec_to_wdec(value_2);
  int ret = 0, flag = 1;
  if (!val1.sig && val2.sig) {
    ret = 1;
    flag = 0;
  }
  if (val1.sig && !val2.sig && flag) {
    ret = 0;
    flag = 0;
  }
  if (flag) {
    normaliz(&val1, &val2);
    int cmp = compare(val1, val2);
    if (cmp == 1) {
      if (!val1.sig)
        ret = 1;
      else
        ret = 0;
    } else if (cmp == 2) {
      if (val1.sig)
        ret = 1;
      else
        ret = 0;
    }
  }
  return ret;
}