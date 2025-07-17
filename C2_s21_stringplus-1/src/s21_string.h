#ifndef S21_STRING_H_
#define S21_STRING_H_

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_NULL ((void *)0)
#define SIZE_NUM 128

typedef long unsigned s21_size_t;

typedef struct {
  int left_align;
  int show_sign;
  int space_sign;
  int zero_pad;
  int width;
  int alt_form;
  int precision;
  int h_modifier;
  int l_modifier;
  int L_modifier;
} format_specificator;

typedef struct {
  int suppress_assign;
  int width;
  int precision;
  int length;
  char specifier;
} format_specifier;

//реализации функции memchr, которая ищет первое вхождение заданного символа в
//заданном блоке памяти:
void *s21_memchr(const void *str, int c, s21_size_t n);

//реализация функции memcmp, которая сравнивает два блока памяти:
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

//реализация функции memcpy, которая копирует n байт из области памяти, на
//которую указывает src, в область памяти, на которую указывает dest:
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

//реализация функции memset, которая заполняет первые n байт области памяти, на
//которую указывает str, значением c
void *s21_memset(void *str, int c, s21_size_t n);

//реализация функции strncat, которая добавляет строку, на которую указывает
// src, в конец строки, на которую указывает dest, но не более чем n символов:
char *s21_strncat(char *dest, const char *src, s21_size_t n);

//реализация функции strchr, которая находит первое вхождение символа c в строке
// str и возвращает указатель на это вхождение:
char *s21_strchr(const char *str, int c);

//реализация функции strcmp, которая предназначена для сравнения первых n
//символов двух строк str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

/*
реализация функции strncpy, которая копирует до n символов из строки src в
строку dest. Если длина src меньше n, то dest будет дополнен нулями до n
символов. Если длина src больше или равна n, то функция просто копирует первые n
символов без добавления завершающего нуля.
*/
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

/*
реализация функции strcspn, которая вычисляет длину начальной части строки str1,
которая не содержит ни одного из символов, присутствующих в строке str2. То есть
она возвращает количество символов в str1 до первого появления любого символа из
str2.
*/
s21_size_t s21_strcspn(const char *str1, const char *str2);

//реализация функции strlen, которая возвращает длину строки
s21_size_t s21_strlen(const char *str);

/*
реализация функции strpbrk, которая ищет первое вхождение любого из символов
строки str2 в строке str1 и возвращает указатель на это вхождение. Если ни один
из символов строки str2 не найден в строке str1, функция возвращает NULL.
*/
char *s21_strpbrk(const char *str1, const char *str2);

/*
реализация функции strrchr, которая ищет последнее вхождение символа c в строке
str и возвращает указатель на это вхождение. Если символ не найден, функция
возвращает NULL.
*/
char *s21_strrchr(const char *str, int c);

/*
реализация функции strstr, которая ищет первое вхождение подстроки needle в
строке haystack и возвращает указатель на это вхождение. Если подстрока не
найдена, функция возвращает NULL
*/
char *s21_strstr(const char *haystack, const char *needle);

/*
реализация функции strtok, которая используется для разбиения строки на
подстроки (токены), разделенные символами из строки-разделителя delim. Она
изменяет исходную строку, заменяя символы-разделители на нулевые символы ('\0')
и возвращает указатель на текущий токен. Последующие вызовы strtok с NULL в
качестве первого аргумента продолжают разбиение оставшейся части строки.
*/
char *s21_strtok(char *str, const char *delim);

//реализация функции strerror, которая используется для получения текстового
//сообщения, соответствующего коду ошибки, переданному в качестве аргумента.
char *s21_strerror(int errnum);

//реализация функции sprintf, которая используется для форматирования строки и
//записи результата в заданный буфер.
int s21_sprintf(char *str, const char *format, ...);

/*
реализация функции sscanf, которая используется для чтения данных из строки в
соответствии с заданным форматом и записи этих данных в переменные, переданные
по адресу.
*/
int s21_sscanf(const char *str, const char *format, ...);

// Функция для преобразования строки в верхний регистр
void *s21_to_upper(const char *str);

// Функция для преобразования строки в нижний регистр
void *s21_to_lower(const char *str);

/*
Функция предназначена для вставки строки str в другую строку src, начиная с
указанного индекса start_index. Эта функция возвращает указатель на новую строку
с вставленным значением.
*/
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

// Проверка, содержит ли символы trim_chars символ c
int s21_is_trim_char(char c, const char *trim_chars);

// Функция для удаления указанных символов из начала и конца строки
void *s21_trim(const char *src, const char *trim_chars);

#endif