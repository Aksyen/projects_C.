#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;

  s21_w_dec val = dec_to_wdec(value);
  int ret = 0;

  // Если степень экспоненты равна нулю, то значение уже целое
  if (val.exp == 0) {
    *result = value;
  } else {
    s21_decimal temp = {{0, 0, 0, 0}};
    s21_decimal half = {{5, 0, 0, 65536}};

    // Добавляем/вычитаем половину в зависимости от знака
    if (val.sig) {
      ret = s21_sub(value, half, &temp);
    } else {
      ret = s21_add(value, half, &temp);
    }

    // Трэнкатируем результат, чтобы получить окончательное округление
    if (!ret) {
      ret = s21_truncate(temp, result);
    }
  }

  return ret;
}

// int s21_round(s21_decimal value, s21_decimal *result) {
//   if (result == NULL) return 1;

//   s21_w_dec val = dec_to_wdec(value);
//   int ret = 0, exp = val.exp, sig = val.sig;

//   // Если степень экспоненты равна нулю, то значение уже целое
//   if (!exp) {
//     *result = value;
//   } else {
//     s21_w_dec half = {{5, 0, 0, 0, 0, 0}, 1, 0};
//     const s21_w_dec ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
//     normaliz(&val, &half);
//     val = wdec_sum(val, half);
//     for (int i = 0; i < exp; i++) val = wdec_div(val, ten);
//     val.exp = 0;
//     val.sig = sig;
//     ret = check_rew_trans(val);
//     if (!ret)
//       *result = wdec_to_dec(val);
//     else
//       ret = 1;
//   }

//   return ret;
// }
