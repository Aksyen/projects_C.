#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;

  s21_w_dec val = dec_to_wdec(value);
  int ret = 0;
  // Если степень экспоненты равна нулю, то значение уже целое
  if (val.exp == 0) {
    *result = value;

  } else {
    // Получаем целую часть путем обрезания
    ret = s21_truncate(value, result);

    if (!ret && val.sig) {
      s21_decimal value_2 = {{1, 0, 0, -2147483648}};
      ret = s21_add(*result, value_2, result);
    }
  }

  return ret;
}
