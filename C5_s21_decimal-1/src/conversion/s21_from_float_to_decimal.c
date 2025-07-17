

#include "../common/s21_common.h"
#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int return_error = 0;
  if (isnan(src) || isinf(src)) {
    return_error = 1;
  } else {
    char line[30] = {0};
    int i = 0, j = 0, k, mnt, exp;
    s21_w_dec dec = {{0, 0, 0, 0, 0, 0}, 0, 0};
    s21_decimal zero = {{0, 0, 0, 0}};
    sprintf(line, "%.6e", src);
    k = strlen(line);
    while (j < k) {
      if (line[j] == 'e') line[j] = ' ';
      if ((line[j] >= '0' && line[j] <= '9') || line[j] == '-' ||
          line[j] == ' ')
        line[i++] = line[j++];
      else
        j++;
    }
    line[i] = 0;
    sscanf(line, "%d %d", &mnt, &exp);
    if (mnt >= 0)
      dec.bits[0] = mnt;
    else {
      dec.sig = 1;
      dec.bits[0] = mnt * -1;
    }
    dec.exp = 6 - exp;

    if (!check_rew_trans(dec))
      *dst = wdec_to_dec(dec);
    else {
      *dst = zero;
      return_error = 1;
    }
  }
  return return_error;
}