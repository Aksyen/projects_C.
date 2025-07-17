#ifndef S21_COMMON_H
#define S21_COMMON_H

// #include "../s21_decimal.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#define _2(bit) (1U << bit)
#define IBS (unsigned char)(sizeof(int) * 8)
#define BL IBS * 6

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[6];
  int exp;
  int sig;  // [0 + ] [1 - ]
} s21_w_dec;

// Получение статуса произвольного бита
int get_bit(const s21_w_dec decimal, const int bnum);

// Проверка на возможность преобразования в decimal
// 0-можно 1-большое 2-маленькое
int check_rew_trans(const s21_w_dec decimal);

// Сравнение без учета знака и экспонент
// (0 =) (1 dec1 > dec2) (2 dec1 < dec2)
int compare(s21_w_dec dec1, s21_w_dec dec2);

// Количество нулевых старших бит
int num_zero_bit(s21_w_dec decimal);

// Установка произвольного бита
s21_w_dec set_bit(s21_w_dec decimal, const int bnum);

// Сброс произвольного бита
s21_w_dec reset_bit(s21_w_dec decimal, const int bnum);

// Преобразование базового decimal в расширенную структуру
// для удобства дальнейшей обработки
s21_w_dec dec_to_wdec(const s21_decimal decimal);

// Преобразование s21_w_dec в s21_decimal
// предварительно необходимо сделать проверку check_rew_trans
s21_decimal wdec_to_dec(const s21_w_dec decimal);

// Сдвиг влево
s21_w_dec shift_l(s21_w_dec decimal);

// Сдвиг вправо
s21_w_dec shift_r(s21_w_dec decimal);

// Суммирование служебное без знака и учета экспонент
s21_w_dec wdec_sum(const s21_w_dec dec1, const s21_w_dec dec2);

// Вычитание служебное без знака и учета экспонент
s21_w_dec wdec_sub(const s21_w_dec dec1, const s21_w_dec dec2);

// Умножение служебное без знака и учета экспонент
s21_w_dec wdec_mul(const s21_w_dec dec1, const s21_w_dec dec2);

// Деление целочисленное служебное без знака без остатка и учета экспонент
s21_w_dec wdec_div(const s21_w_dec dividend, const s21_w_dec divisor);

// Остаток целочисленного деления служебное без знака без остатка и учета
// экспонент
s21_w_dec wdec_rem(const s21_w_dec dividend, const s21_w_dec divisor);

// Уравнивание экспоненты
void normaliz(s21_w_dec *dec1, s21_w_dec *dec2);

// Максимальное увеличение экспоненты
s21_w_dec to_max_exp(const s21_w_dec decimal);

// Распечатать содержимое структуры
void print_wdec(const s21_w_dec dec);

// Распечатать содержимое структуры
void print_dec(const s21_decimal dec);

#endif  // S21_COMMON_H