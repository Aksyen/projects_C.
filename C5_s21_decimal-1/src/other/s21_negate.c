#include "../s21_decimal.h"

#define SIGN_MASK 0x80000000  // Маска для выделения бита знака

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) {
    return 1;  // Ошибка вычисления, если указатель на результат NULL
  }

  // Копируем все биты из value в result
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->bits[3] = value.bits[3];

  // Инвертируем знак
  result->bits[3] ^= SIGN_MASK;

  return 0;  // OK
}