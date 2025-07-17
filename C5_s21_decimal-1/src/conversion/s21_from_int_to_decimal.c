#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;

  // Обнуляем все поля dst
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;

  // Определяем знак числа
  if (src < 0) {
    dst->bits[3] = (unsigned int)1
                   << 31;  // Устанавливаем знак отрицательного числа
    src = -src;  // Берем абсолютное значение src
  }

  // Записываем значение в первую часть bits (32 младших бита)
  dst->bits[0] = src;

  // Функция выполнена успешно
  return 0;
}
