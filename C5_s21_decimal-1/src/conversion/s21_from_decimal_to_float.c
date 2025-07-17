
#include "../s21_decimal.h"
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double result = 0;
  int scale = 0;
  long long temp_int = 0;
  for (unsigned i = 0; i < 96; i++) {
    // if bit i is set
    if ((src.bits[i / 32] & (1u << i % 32)) != 0) {
      temp_int += pow(2, i);
    }
  }
  // calculate 16-23 bit in bits[3]
  result = (float)temp_int;
  if ((scale = (src.bits[3] >> 16) & 0xFF) > 0) {
    for (int i = scale; i > 0; i--) {
      result /= 10.0;
    }
  }
  int error_code = 0;
  if ((result < FLT_MIN && result > 0.0) || result > FLT_MAX) {
    *dst = 0;
    error_code = 1;
  } else {
    if (src.bits[3] < 0) result *= -1;
    *dst = (float)result;
  }
  return error_code;
}