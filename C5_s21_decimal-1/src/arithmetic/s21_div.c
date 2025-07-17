#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_w_dec quotient = {{0, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec dividend = dec_to_wdec(value_1);
  s21_w_dec divisor = dec_to_wdec(value_2);
  int ret = 0;
  if (!compare(dividend, quotient) && divisor.sig) quotient.sig = 1;
  *result = wdec_to_dec(quotient);
  if (compare(dividend, quotient) && dividend.exp < 29 && divisor.exp < 29) {
    if (compare(divisor, quotient)) {
      dividend = to_max_exp(dividend);
      int exp = dividend.exp - divisor.exp;
      int sig;
      if ((dividend.sig && divisor.sig) || (!dividend.sig && !divisor.sig))
        sig = 0;
      else
        sig = 1;
      quotient = wdec_div(dividend, divisor);
      quotient.exp = exp;
      quotient.sig = sig;
      ret = check_rew_trans(quotient);
      if (!ret) *result = wdec_to_dec(quotient);
    } else
      ret = 3;
  }
  return ret;
}