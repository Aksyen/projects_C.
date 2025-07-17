#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_w_dec res = {{0, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec mul1 = dec_to_wdec(value_1);
  s21_w_dec mul2 = dec_to_wdec(value_2);
  int ret = 0, flag = 1;
  if ((!compare(mul1, res) || !compare(mul2, res)) && (mul1.sig || mul2.sig)) {
    res.sig = 1;
    flag = 0;
  }
  *result = wdec_to_dec(res);
  if (flag && mul1.exp < 29 && mul2.exp < 29) {
    int exp = mul1.exp + mul2.exp;
    int sig;
    if ((mul1.sig && mul2.sig) || (!mul1.sig && !mul2.sig))
      sig = 0;
    else
      sig = 1;
    res = wdec_mul(mul1, mul2);
    res.exp = exp;
    res.sig = sig;
    ret = check_rew_trans(res);
    if (!ret) *result = wdec_to_dec(res);
  }
  return ret;
}