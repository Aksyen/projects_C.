#include "s21_common.h"

s21_w_dec dec_to_wdec(const s21_decimal decimal) {
  s21_w_dec tmp = {
      {decimal.bits[0], decimal.bits[1], decimal.bits[2], 0, 0, 0}, 0, 0};
  for (int i = 0; i < 8; i++) {
    if (decimal.bits[3] & _2((i + 16))) tmp.exp |= _2(i);
  }
  if (decimal.bits[3] & (_2(31))) tmp.sig = 1;
  return tmp;
}

s21_decimal wdec_to_dec(const s21_w_dec decimal) {
  s21_w_dec dec_tmp = decimal;
  s21_w_dec remainder, dec_tmp2;
  const s21_w_dec ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
  const s21_w_dec five = {{5, 0, 0, 0, 0, 0}, 0, 0};
  const s21_w_dec e8 = {{100000000, 0, 0, 0, 0, 0}, 0, 0};
  int sig = dec_tmp.sig, exp;
  while (num_zero_bit(dec_tmp) < 68) {
    exp = dec_tmp.exp;
    dec_tmp = wdec_div(dec_tmp, e8);
    dec_tmp.exp = exp - 8;
  }
  while (num_zero_bit(dec_tmp) < 96 || dec_tmp.exp > 28) {
    exp = dec_tmp.exp;
    remainder = wdec_rem(dec_tmp, ten);
    int cmp = compare(remainder, five);
    if (cmp == 2) {
      dec_tmp = wdec_div(dec_tmp, ten);
    } else if (cmp == 1) {
      dec_tmp = wdec_sum(dec_tmp, ten);
      dec_tmp = wdec_div(dec_tmp, ten);
    } else if (cmp == 0) {
      dec_tmp2 = wdec_sub(dec_tmp, ten);
      if (get_bit(dec_tmp2, 0)) {
        dec_tmp = wdec_sum(dec_tmp, ten);
        dec_tmp = wdec_div(dec_tmp, ten);
      }
    }
    dec_tmp.exp = exp - 1;
  }
  if (dec_tmp.exp) {
    const s21_w_dec zero = {{0, 0, 0, 0, 0, 0}, 0, 0};
    remainder = wdec_rem(dec_tmp, ten);
    while (!compare(remainder, zero) && dec_tmp.exp > 0) {
      exp = dec_tmp.exp;
      dec_tmp = wdec_div(dec_tmp, ten);
      dec_tmp.exp = exp - 1;
      remainder = wdec_rem(dec_tmp, ten);
    }
  }
  s21_decimal tmp = {{dec_tmp.bits[0], dec_tmp.bits[1], dec_tmp.bits[2], 0}};
  for (int i = 0; i < 8; i++) {
    if (dec_tmp.exp & _2(i)) tmp.bits[3] |= _2((i + 16));
  }
  if (sig) tmp.bits[3] |= _2(31);
  return tmp;
}

int get_bit(const s21_w_dec decimal, const int bnum) {
  return (decimal.bits[bnum / IBS] & _2(bnum % IBS)) != 0;
}

s21_w_dec set_bit(s21_w_dec decimal, const int bnum) {
  decimal.bits[bnum / IBS] |= _2(bnum % IBS);
  return decimal;
}

// s21_w_dec reset_bit(s21_w_dec decimal, const int bnum) {
//   decimal.bits[bnum / IBS] &= ~(_2(bnum % IBS));
//   return decimal;
// }

s21_w_dec shift_l(s21_w_dec decimal) {
  for (int i = 5; i >= 0; i--) {
    decimal.bits[i] = decimal.bits[i] << 1;
    if (i) {
      if ((decimal.bits[i - 1] & _2(31)) != 0 ? 1 : 0) decimal.bits[i] |= _2(0);
    }
  }
  return decimal;
}

s21_w_dec shift_r(s21_w_dec decimal) {
  for (int i = 0; i < 6; i++) {
    decimal.bits[i] = decimal.bits[i] >> 1;
    if (i < 5) {
      if ((decimal.bits[i + 1] & _2(0)) != 0 ? 1 : 0) decimal.bits[i] |= _2(31);
    }
  }
  return decimal;
}

s21_w_dec wdec_sum(const s21_w_dec dec1, const s21_w_dec dec2) {
  s21_w_dec tmp = {{0, 0, 0, 0, 0, 0}, 0, 0};
  int overflow = 0;
  for (int i = 0; i < BL; i++) {
    int b_dec1 = get_bit(dec1, i);
    int b_dec2 = get_bit(dec2, i);
    if (overflow) {
      if (b_dec1 && b_dec2) {
        tmp = set_bit(tmp, i);
      } else if (!b_dec1 && !b_dec2) {
        tmp = set_bit(tmp, i);
        overflow = 0;
      }
    } else {
      if (b_dec1 && b_dec2) {
        overflow = 1;
      } else if (!b_dec1 && !b_dec2) {
        ;
      } else
        tmp = set_bit(tmp, i);
    }
  }
  return tmp;
}

s21_w_dec wdec_sub(const s21_w_dec dec1, const s21_w_dec dec2) {
  s21_w_dec tmp = {{0, 0, 0, 0, 0, 0}, 0, 0};
  int loan = 0;
  for (int i = 0; i < BL; i++) {
    int b_dec1 = get_bit(dec1, i);
    int b_dec2 = get_bit(dec2, i);
    if (loan) {
      if (b_dec1 && !b_dec2) {
        loan = 0;
      } else if ((!b_dec1 && !b_dec2) || (b_dec1 && b_dec2)) {
        tmp = set_bit(tmp, i);
      }
    } else {
      if (b_dec1 && !b_dec2) {
        tmp = set_bit(tmp, i);
      } else if (!b_dec1 && b_dec2) {
        tmp = set_bit(tmp, i);
        loan = 1;
      }
    }
  }
  return tmp;
}

s21_w_dec wdec_mul(const s21_w_dec dec1, const s21_w_dec dec2) {
  s21_w_dec tmp = {{0, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec mult = dec1;
  for (int i = 0; i < BL / 2; i++) {
    if (get_bit(dec2, i)) tmp = wdec_sum(tmp, mult);
    mult = shift_l(mult);
  }
  return tmp;
}

s21_w_dec wdec_div(const s21_w_dec dividend, const s21_w_dec divisor) {
  s21_w_dec quotient = {{0, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec remainder = dividend;
  const s21_w_dec zero = {{0, 0, 0, 0, 0, 0}, 0, 0};
  const s21_w_dec one = {{1, 0, 0, 0, 0, 0}, 0, 0};
  if (compare(zero, divisor)) {
    if (compare(dividend, divisor) == 0 || compare(dividend, divisor) == 2) {
      if (!compare(dividend, divisor)) quotient.bits[0] = 1;
    } else {
      while (compare(remainder, divisor) < 2) {
        s21_w_dec divisor_tmp = divisor;
        s21_w_dec quotient_tmp = one;
        while (compare(remainder, divisor_tmp) < 2) {
          quotient_tmp = shift_l(quotient_tmp);
          divisor_tmp = shift_l(divisor_tmp);
        }
        quotient_tmp = shift_r(quotient_tmp);
        quotient = wdec_sum(quotient, quotient_tmp);
        divisor_tmp = shift_r(divisor_tmp);
        remainder = wdec_sub(remainder, divisor_tmp);
      }
    }
  }
  return quotient;
}

s21_w_dec wdec_rem(const s21_w_dec dividend, const s21_w_dec divisor) {
  s21_w_dec quotient = {{0, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec remainder = dividend;
  const s21_w_dec zero = {{0, 0, 0, 0, 0, 0}, 0, 0};
  const s21_w_dec one = {{1, 0, 0, 0, 0, 0}, 0, 0};
  int cmp = compare(zero, divisor);
  if (cmp) {
    cmp = compare(dividend, divisor);
    if (cmp == 0 || cmp == 2) {
      if (!cmp) remainder = zero;
    } else {
      while (cmp < 2) {
        s21_w_dec divisor_tmp = divisor;
        s21_w_dec quotient_tmp = one;
        while (cmp < 2) {
          quotient_tmp = shift_l(quotient_tmp);
          divisor_tmp = shift_l(divisor_tmp);
          cmp = compare(remainder, divisor_tmp);
        }
        quotient_tmp = shift_r(quotient_tmp);
        quotient = wdec_sum(quotient, quotient_tmp);
        divisor_tmp = shift_r(divisor_tmp);
        remainder = wdec_sub(remainder, divisor_tmp);
        cmp = compare(remainder, divisor);
      }
    }
  }
  return remainder;
}

s21_w_dec to_max_exp(const s21_w_dec decimal) {
  const s21_w_dec ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
  const s21_w_dec e18 = {{-1486618624, 232830643, 0, 0, 0, 0}, 0, 0};
  const s21_w_dec zero = {{0, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec dec_tmp = decimal;
  int sig = decimal.sig;
  if (compare(decimal, zero)) {
    int exp = dec_tmp.exp;
    dec_tmp = wdec_mul(dec_tmp, e18);
    dec_tmp.exp = exp + 18;
    while (num_zero_bit(dec_tmp) > 4) {
      exp = dec_tmp.exp;
      dec_tmp = wdec_mul(dec_tmp, ten);
      dec_tmp.exp = exp + 1;
    }
    dec_tmp.sig = sig;
  }
  return dec_tmp;
}

void normaliz(s21_w_dec *dec1, s21_w_dec *dec2) {
  int sh = dec1->exp - dec2->exp;
  int exp, sig;
  s21_w_dec ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
  if (sh > 0) {
    exp = dec2->exp;
    sig = dec2->sig;
    for (int i = 0; i < sh; i++) {
      *dec2 = wdec_mul(*dec2, ten);
      exp++;
    }
    dec2->exp = exp;
    dec2->sig = sig;
  }
  if (sh < 0) {
    exp = dec1->exp;
    sig = dec1->sig;
    for (int i = 0; i > sh; i--) {
      *dec1 = wdec_mul(*dec1, ten);  // s21_w_dec quotient_tmp;
      exp++;
    }
    dec1->exp = exp;
    dec1->sig = sig;
  }
}

int compare(s21_w_dec dec1, s21_w_dec dec2) {
  int res = 0;
  for (int i = BL - 1; i >= 0 && !res; i--) {
    int b1 = get_bit(dec1, i);
    int b2 = get_bit(dec2, i);
    if (b1 > b2) res = 1;
    if (b1 < b2) res = 2;
  }
  return res;
}

int num_zero_bit(s21_w_dec decimal) {
  int res = 0;
  for (int i = BL - 1; i >= 0 && !get_bit(decimal, i); i--) res++;
  return res;
}

// void print_wdec(const s21_w_dec dec) {
//   printf("\n");
//   for (int i = 0; i < 6; i++) printf("%d ", dec.bits[5 - i]);
//   printf("exp = %d ", dec.exp);
//   if (dec.sig)
//     printf("-");
//   else
//     printf("+");
// }

// void print_dec(const s21_decimal dec) {
//   printf("\n");
//   for (int i = 0; i < 4; i++) printf("%x ", dec.bits[3 - i]);
// }

int check_rew_trans(const s21_w_dec decimal) {
  int ret = 0, exp, sig;
  const s21_w_dec zero = {{0, 0, 0, 0, 0, 0}, 0, 0};
  const s21_w_dec ten = {{10, 0, 0, 0, 0, 0}, 0, 0};
  const s21_w_dec e9 = {{1000000000, 0, 0, 0, 0, 0}, 0, 0};
  s21_w_dec dec_tmp = decimal;
  sig = dec_tmp.sig;
  while (num_zero_bit(dec_tmp) < 67) {
    exp = dec_tmp.exp;
    dec_tmp = wdec_div(dec_tmp, e9);
    dec_tmp.exp = exp - 9;
  }
  dec_tmp.sig = sig;
  if (num_zero_bit(dec_tmp) < 96) {
    if (!dec_tmp.exp) {
      if (dec_tmp.sig)
        ret = 2;
      else
        ret = 1;
    } else {
      while (num_zero_bit(dec_tmp) < 96 && dec_tmp.exp > 0) {
        exp = dec_tmp.exp;
        dec_tmp = wdec_div(dec_tmp, ten);
        dec_tmp.exp = exp - 1;
      }
      if (num_zero_bit(dec_tmp) < 96) {
        if (decimal.sig)
          ret = 2;
        else
          ret = 1;
      }
    }
  }
  if (dec_tmp.exp > 28) {
    while (dec_tmp.exp > 28 && compare(dec_tmp, zero)) {
      exp = dec_tmp.exp;
      dec_tmp = wdec_div(dec_tmp, ten);
      dec_tmp.exp = exp - 1;
    }
    if (dec_tmp.exp > 28) ret = 2;
  }
  return ret;
}
