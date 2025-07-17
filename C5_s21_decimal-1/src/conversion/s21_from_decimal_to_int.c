#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) return 1;  // Проверка указателя на NULL

  // Инициализация dst
  *dst = 0;
  s21_decimal temp;
  s21_round(src, &temp);  // Округляем значение до ближайшего целого
  s21_decimal max_int = {{2147483647, 0, 0, 0}};             // 2147483647
  s21_decimal min_int = {{-2147483648, 0, 0, -2147483648}};  // -2147483648
  int ret = 0;

  // Проверка на переполнение для типа int
  if (s21_is_greater(temp, max_int) || s21_is_less(temp, min_int)) {
    ret = 1;
  } else {
    unsigned int sign = (unsigned int)temp.bits[3] >> 31;
    int value = temp.bits[0];
    // Применение знака
    if (sign) {
      *dst = -value;
    } else {
      *dst = value;
    }
  }
  return ret;  // Успех или ошибка в зависимости от ret
}
