#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_w_dec res = {{0, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec val1 = dec_to_wdec(value_1);
  s21_w_dec val2 = dec_to_wdec(value_2);
  int ret = 0, exp = 0, flag = 1, cmp;
  *result = wdec_to_dec(res);
  if (val1.exp > 28 || val2.exp > 28) flag = 0;
  if (!compare(val1, res) && flag) {
    res = val2;
    flag = 0;
  }
  if (!compare(val2, res) && flag) {
    res = val1;
    flag = 0;
  }
  if (flag) {
    normaliz(&val1, &val2);
    cmp = compare(val1, val2);
    exp = val1.exp;
  }
  if (!val1.sig && !val2.sig && flag) {
    res = wdec_sum(val1, val2);
    res.sig = 0;
    flag = 0;
  }
  if (val1.sig && val2.sig && flag) {
    res = wdec_sum(val1, val2);
    res.sig = 1;
    flag = 0;
  }
  if (val1.sig && flag) {
    if (cmp < 2) {
      res = wdec_sub(val1, val2);
      res.sig = 1;
    }
    if (cmp == 2) {
      res = wdec_sub(val2, val1);
      res.sig = 0;
    }
    flag = 0;
  }
  if (val2.sig && flag) {
    if (cmp == 1) {
      res = wdec_sub(val1, val2);
      res.sig = 0;
    }
    if (cmp == 2) {
      res = wdec_sub(val2, val1);
      res.sig = 1;
    }
    // flag = 0;
  }
  res.exp = exp;
  ret = check_rew_trans(res);
  if (!ret) *result = wdec_to_dec(res);
  return ret;
}