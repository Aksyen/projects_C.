#include <check.h>
#include <errno.h>
#include <string.h>

#include "s21_string.h"

// Тесты для функции s21_memchr
START_TEST(test_s21_memchr) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_memchr(str, 'o', 13), memchr(str, 'o', 13));
  ck_assert_ptr_eq(s21_memchr(str, 'z', 13), memchr(str, 'z', 13));
}
END_TEST

// Тесты для функции s21_memcmp
START_TEST(test_s21_memcmp) {
  const char *str1 = "Hello";
  const char *str2 = "Hello";
  const char *str3 = "World";
  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
  ck_assert_int_eq(s21_memcmp(str1, str3, 5), memcmp(str1, str3, 5));
  ck_assert_int_eq(s21_memcmp(str2, str3, 5), memcmp(str2, str3, 5));

  const char str[] = "Hello, world!";
  const char str0[] = "Hello,\n world";
  const char str10[] = "Hello, worLd";
  s21_size_t len = s21_strlen(str);
  ck_assert_int_eq(s21_memcmp(str, str0, len), memcmp(str, str0, len));
  ck_assert_int_eq(s21_memcmp(str, str10, len), memcmp(str, str10, len));
}
END_TEST

// Тесты для функции s21_memcpy
START_TEST(test_s21_memcpy) {
  char dest1[20] = {0};
  char dest2[20] = {0};
  const char *src = "Hello, world!";
  ck_assert_str_eq(s21_memcpy(dest1, src, 13), memcpy(dest2, src, 13));
}
END_TEST

// Тесты для функции s21_memset
START_TEST(test_s21_memset) {
  char str1[20] = "Hello, world!";
  char str2[20] = "Hello, world!";
  ck_assert_str_eq(str1, str2);
}
END_TEST

// Тесты для функции s21_strncat
START_TEST(test_s21_strncat) {
  char dest1[20] = "Hello";
  char dest2[20] = "Hello";
  const char *src = ", world!";
  ck_assert_str_eq(s21_strncat(dest1, src, 8), strncat(dest2, src, 8));
}
END_TEST

// Тесты для функции s21_strchr
START_TEST(test_s21_strchr) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
}
END_TEST

// Тесты для функции s21_strncmp
START_TEST(test_s21_strncmp) {
  const char *str1 = "Hello";
  const char *str2 = "Hello";
  const char *str3 = "HeLLo";

  ck_assert_int_eq(s21_strncmp(str1, str2, 2), strncmp(str1, str2, 2));
  ck_assert_int_eq(s21_strncmp(str2, str1, 2), strncmp(str2, str1, 2));
  ck_assert_int_eq(s21_strncmp(str2, str3, 2), strncmp(str2, str3, 2));
}
END_TEST

// Тесты для функции s21_strncpy
START_TEST(test_s21_strncpy) {
  const char str1[] = "test of string";
  char dest1[15] = "";
  char expected1[15] = "";

  const char str2[] = "test\0";
  char dest2[5] = "";
  char expected2[5] = "";

  const char str3[] = "test ";
  char dest3[] = "crushcrush";
  char expected3[] = "crushcrush";

  // Используем оригинальную strncpy для получения ожидаемых результатов
  strncpy(expected1, str1, 5);
  strncpy(expected2, str2, 4);
  strncpy(expected3, str3, 10);

  // Сравниваем результаты s21_strncpy с оригинальной strncpy
  ck_assert_str_eq(expected1, s21_strncpy(dest1, str1, 5));
  ck_assert_str_eq(expected2, s21_strncpy(dest2, str2, 4));
  ck_assert_str_eq(expected3, s21_strncpy(dest3, str3, 10));
}
END_TEST

// Тесты для функции s21_strcspn
START_TEST(test_s21_strcspn) {
  const char *str1 = "Hello, world!";
  const char *str2 = "oe";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// Тесты для функции s21_strlen
START_TEST(test_s21_strlen) {
  const char *str = "Hello, world!";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// Тесты для функции s21_strpbrk
START_TEST(test_s21_strpbrk) {
  const char *str1 = "Hello, world!";
  const char *str2 = "oe";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// Тесты для функции s21_strrchr
START_TEST(test_s21_strrchr) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

// Тесты для функции s21_strstr
START_TEST(test_s21_strstr) {
  const char *str1 = "Hello, world!";
  const char *str2 = "world";
  ck_assert_ptr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

// Тесты для функции s21_strtok
START_TEST(test_s21_strtok) {
  char str1[20] = "Hello, world!";
  char str2[20] = "Hello, world!";
  const char *delim = ", ";
  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));
  ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

// Тесты для функции s21_strerror
START_TEST(test_s21_strerror) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(2), strerror(2));
  ck_assert_str_eq(s21_strerror(22), strerror(22));
  ck_assert_str_eq(s21_strerror(90), strerror(90));
  ck_assert_str_eq(s21_strerror(5), strerror(5));
  ck_assert_str_eq(s21_strerror(14), strerror(14));
  ck_assert_str_eq(s21_strerror(60), strerror(60));
  ck_assert_str_eq(s21_strerror(78), strerror(78));
}
END_TEST

START_TEST(test_string) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Hello, %s!", "world");
  sprintf(buffer2, "Hello, %s!", "world");
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_integer) {
  char buffer[100];
  char buffer2[100];
  int n1 = 42;
  int n2 = 42;
  int x1 = s21_sprintf(buffer, "Number: %d", n1);
  int x2 = sprintf(buffer2, "Number: %d", n2);
  ck_assert_str_eq(buffer, buffer2);
  ck_assert_int_eq(x1, x2);
  x1 = s21_sprintf(buffer, "Number: %n", &n1);
  x2 = sprintf(buffer2, "Number: %n", &n2);
  ck_assert_str_eq(buffer, buffer2);
  ck_assert_int_eq(x1, x2);
}
END_TEST

START_TEST(test_unsigned) {
  char str[80];
  char str_orig[80];
  unsigned int a = 2345;

  int res_1 = s21_sprintf(str, "%10.5u", a);
  int res_1_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%10.5u", a);
  int res_2_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5u", a);
  int res_3_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%0u", a);
  int res_4_orig = sprintf(str_orig, "%0u", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%-u", a);
  int res_5_orig = sprintf(str_orig, "%-u", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%u", a);
  int res_6_orig = sprintf(str_orig, "%u", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%5u", a);
  int res_7_orig = sprintf(str_orig, "%5u", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "%05u", a);
  int res_8_orig = sprintf(str_orig, "%05u", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%-5u", a);
  int res_9_orig = sprintf(str_orig, "%-5u", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%.5u", a);
  int res_10_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%.5u", a);
  int res_11_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%-.5u", a);
  int res_12_orig = sprintf(str_orig, "%-.5u", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "%-10.5u", a);
  int res_13_orig = sprintf(str_orig, "%-10.5u", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = s21_sprintf(str, "%3.5u", a);
  int res_14_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = s21_sprintf(str, "%-3.5u", a);
  int res_15_orig = sprintf(str_orig, "%-3.5u", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = s21_sprintf(str, "%6.2u", a);
  int res_16_orig = sprintf(str_orig, "%6.2u", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = s21_sprintf(str, "%3.2u", a);
  int res_17_orig = sprintf(str_orig, "%3.2u", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = s21_sprintf(str, "%01u", a);
  int res_18_orig = sprintf(str_orig, "%01u", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = s21_sprintf(str, "%hu", (unsigned short)a);
  int res_19_orig = sprintf(str_orig, "%hu", (unsigned short)a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = s21_sprintf(str, "%lu", (unsigned long)a);
  int res_20_orig = sprintf(str_orig, "%lu", (unsigned long)a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);
  long int b = 15166;
  int res_21 = s21_sprintf(str, "%ld", b);
  int res_21_orig = sprintf(str_orig, "%ld", b);
  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_prc_test) {
  char str[80];
  char str_orig[80];

  int res_1 = s21_sprintf(str, "%%");
  int res_1_orig = sprintf(str_orig, "%%");
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "abc%%defg");
  int res_5_orig = sprintf(str_orig, "abc%%defg");

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(test_short) {
  char buffer[100];
  char buffer2[100];
  int x1 = s21_sprintf(buffer, "Number: %u", 42u);
  int x2 = sprintf(buffer2, "Number: %u", 42u);
  ck_assert_str_eq(buffer, buffer2);
  ck_assert_int_eq(x1, x2);
  x1 = s21_sprintf(buffer, "Number: %llu", 424846846155666541llu);
  x2 = sprintf(buffer2, "Number: %llu", 424846846155666541llu);
  ck_assert_str_eq(buffer, buffer2);
  ck_assert_int_eq(x1, x2);
}
END_TEST

START_TEST(test_float) {
  char buffer[100];
  char buffer2[100];

  // Сравнение для формата "%.2f"
  int x1 = s21_sprintf(buffer, "Float: %.2f", 3.14159);
  int x2 = sprintf(buffer2, "Float: %.2f", 3.14159);
  ck_assert_str_eq(buffer, buffer2);
  ck_assert_int_eq(x1, x2);
  // Сравнение для формата "%f"
  x1 = s21_sprintf(buffer, "Float: %f", 3.14159);
  x2 = sprintf(buffer2, "Float: %f", 3.14159);
  ck_assert_str_eq(buffer, buffer2);
  ck_assert_int_eq(x1, x2);
  // Сравнение для формата "%lf"
  s21_sprintf(buffer, "Float: %lf", 3.014159);
  sprintf(buffer2, "Float: %lf", 3.014159);
  ck_assert_str_eq(buffer, buffer2);

  // Сравнение для формата "%Lf"
  x1 = s21_sprintf(buffer, "Float: %Lf", 345415415.141595656336L);
  x2 = sprintf(buffer2, "Float: %Lf", 345415415.141595656336L);
  ck_assert_str_eq(buffer, buffer2);
  ck_assert_int_eq(x1, x2);
}
END_TEST

START_TEST(test_o) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Hex: %o", 255);
  sprintf(buffer2, "Hex: %o", 255);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_o_prefix) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Hex with prefix: %#o", 255);
  sprintf(buffer2, "Hex with prefix: %#o", 255);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_pointer) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Pointer: %p", (void *)0xdeadbeef);
  sprintf(buffer2, "Pointer: %p", (void *)0xdeadbeef);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_scientific) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Scientific: %e", 1234.5678);
  sprintf(buffer2, "Scientific: %e", 1234.5678);
  ck_assert_str_eq(buffer, buffer2);
  s21_sprintf(buffer, "Scientific: %Le", 1234.5678L);
  sprintf(buffer2, "Scientific: %Le", 1234.5678L);
  ck_assert_str_eq(buffer, buffer2);
  s21_sprintf(buffer, "Scientific: %#e", 1234.5678);
  sprintf(buffer2, "Scientific: %#e", 1234.5678);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_g_format) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "G format: %g", 1234.5678);
  sprintf(buffer2, "G format: %g", 1234.5678);
  ck_assert_str_eq(buffer, buffer2);
  s21_sprintf(buffer, "G format: %Lg", 1234.5678L);
  sprintf(buffer2, "G format: %Lg", 1234.5678L);
  ck_assert_str_eq(buffer, buffer2);
  s21_sprintf(buffer, "G format: %#g", 1234.5678);
  sprintf(buffer2, "G format: %#g", 1234.5678);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_G_format) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "G format: %G", 1234.5678);
  sprintf(buffer2, "G format: %G", 1234.5678);
  ck_assert_str_eq(buffer, buffer2);
  s21_sprintf(buffer, "G format: %#G", 1234.5678);
  sprintf(buffer2, "G format: %#G", 1234.5678);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_character) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Character: %c", 'A');
  sprintf(buffer2, "Character: %c", 'A');
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_string_left) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "String: %-10s", "left");
  sprintf(buffer2, "String: %-10s", "left");
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_zero_padded) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Zero padded: %05d", 42);
  sprintf(buffer2, "Zero padded: %05d", 42);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_left_aligned) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Left aligned: %-5d", -42);
  sprintf(buffer2, "Left aligned: %-5d", -42);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_sign) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Sign: %+d", 42);
  sprintf(buffer2, "Sign: %+d", 42);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_space) {
  char buffer[100];
  char buffer2[100];
  int a = -55;
  s21_sprintf(buffer, "Space: % d", a);
  sprintf(buffer2, "Space: % d", a);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_alternate) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Alternate: %#x", 42);
  sprintf(buffer2, "Alternate: %#x", 42);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_width) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Width: %*d", 5, 42);
  sprintf(buffer2, "Width: %*d", 5, 42);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_precision) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Precision: %.*f", 3, 3.14159);
  sprintf(buffer2, "Precision: %.*f", 3, 3.14159);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_big_number) {
  char buffer[100];
  char buffer2[100];
  s21_sprintf(buffer, "Big number: %.10Lf", 123456789.123456789L);
  sprintf(buffer2, "Big number: %.10Lf", 123456789.123456789L);
  ck_assert_str_eq(buffer, buffer2);

  s21_sprintf(buffer, "Big number: %lf", 123456789.123456789);
  sprintf(buffer2, "Big number: %lf", 123456789.123456789);
  ck_assert_str_eq(buffer, buffer2);

  s21_sprintf(buffer, "Big number: %10lf", 123456789.123456789);
  sprintf(buffer2, "Big number: %10lf", 123456789.123456789);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

START_TEST(test_complex_format) {
  char buffer[100];
  char buffer2[100];
  double width = 2.4, height = 0.76, depth = 3.14;
  char name[] = "Chair";
  s21_sprintf(buffer, "(%s: %.2lf x %.2lf x %.2lf)", name, width, height,
              depth);
  sprintf(buffer2, "(%s: %.2lf x %.2lf x %.2lf)", name, width, height, depth);
  ck_assert_str_eq(buffer, buffer2);
}
END_TEST

// Тест для целочисленного формата
START_TEST(test_sscanf_int) {
  int value_s21, value_std;
  int ret_s21 = s21_sscanf("123", "%d", &value_s21);
  int ret_std = sscanf("123", "%d", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value_s21, value_std);
  ret_s21 = s21_sscanf("-123", "%d", &value_s21);
  ret_std = sscanf("-123", "%d", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value_s21, value_std);
  ret_s21 = s21_sscanf("+123", "%d", &value_s21);
  ret_std = sscanf("+123", "%d", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value_s21, value_std);

  short value1_s21, value1_std;
  ret_s21 = s21_sscanf("123", "%hd", &value1_s21);
  ret_std = sscanf("123", "%hd", &value1_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value1_s21, value1_std);
  ret_s21 = s21_sscanf("-123", "%hd", &value1_s21);
  ret_std = sscanf("-123", "%hd", &value1_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value1_s21, value1_std);
  ret_s21 = s21_sscanf("+123", "%hd", &value1_s21);
  ret_std = sscanf("+123", "%hd", &value1_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value1_s21, value1_std);

  unsigned char value2_s21, value2_std;
  ret_s21 = s21_sscanf("123", "%hhu", &value2_s21);
  ret_std = sscanf("123", "%hhu", &value2_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value2_s21, value2_std);

  long int value3_s21, value3_std;
  ret_s21 = s21_sscanf("1231548484", "%ld", &value3_s21);
  ret_std = sscanf("1231548484", "%ld", &value3_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value3_s21, value3_std);
  ret_s21 = s21_sscanf("+1231548484", "%ld", &value3_s21);
  ret_std = sscanf("+1231548484", "%ld", &value3_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value3_s21, value3_std);
  ret_s21 = s21_sscanf("-1231548484", "%ld", &value3_s21);
  ret_std = sscanf("-1231548484", "%ld", &value3_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value3_s21, value3_std);

  signed char value4_s21, value4_std;
  ret_s21 = s21_sscanf("123", "%hhd", &value4_s21);
  ret_std = sscanf("123", "%hhd", &value4_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value4_s21, value4_std);
  ret_s21 = s21_sscanf("-123", "%hhd", &value4_s21);
  ret_std = sscanf("-123", "%hhd", &value4_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value4_s21, value4_std);

  unsigned int value5_s21, value5_std;
  ret_s21 = s21_sscanf("123", "%u", &value5_s21);
  ret_std = sscanf("123", "%u", &value5_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value5_s21, value5_std);

  long unsigned int value6_s21, value6_std;
  ret_s21 = s21_sscanf("1231548484", "%lu", &value6_s21);
  ret_std = sscanf("1231548484", "%lu", &value6_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value6_s21, value6_std);

  long long unsigned int value7_s21, value7_std;
  ret_s21 = s21_sscanf("12315484845996", "%llu", &value7_s21);
  ret_std = sscanf("12315484845996", "%llu", &value7_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value7_s21, value7_std);

  long long int value8_s21, value8_std;
  ret_s21 = s21_sscanf("12315484845996", "%lld", &value8_s21);
  ret_std = sscanf("12315484845996", "%lld", &value8_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value8_s21, value8_std);
  ret_s21 = s21_sscanf("-12315484845996", "%lld", &value8_s21);
  ret_std = sscanf("-12315484845996", "%lld", &value8_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value8_s21, value8_std);

  unsigned short int value9_s21, value9_std;
  ret_s21 = s21_sscanf("123", "%hu", &value9_s21);
  ret_std = sscanf("123", "%hu", &value9_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value9_s21, value9_std);
}
END_TEST

// Тест для строки
START_TEST(test_sscanf_string) {
  char str_s21[100], str_std[100];
  int ret_s21 = s21_sscanf("hello", "%99s", str_s21);
  int ret_std = sscanf("hello", "%99s", str_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_str_eq(str_s21, str_std);
}
END_TEST

// Тест для числа с плавающей точкой
START_TEST(test_sscanf_float) {
  double dvalue_s21, dvalue_std;
  int ret_s21 = s21_sscanf("123.456", "%lf", &dvalue_s21);
  int ret_std = sscanf("123.456", "%lf", &dvalue_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_double_eq(dvalue_s21, dvalue_std);

  long double dvalue1_s21, dvalue1_std;
  ret_s21 = s21_sscanf("123555757.456572725", "%Lf", &dvalue1_s21);
  ret_std = sscanf("123555757.456572725", "%Lf", &dvalue1_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_double_eq(dvalue1_s21, dvalue1_std);
}
END_TEST

// Тест для шестнадцатеричного числа
START_TEST(test_sscanf_hex) {
  unsigned int value_s21, value_std;
  int ret_s21 = s21_sscanf("1A3", "%x", &value_s21);
  int ret_std = sscanf("1A3", "%x", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_uint_eq(value_s21, value_std);
}
END_TEST

// Тест для символа
START_TEST(test_sscanf_char) {
  char value_s21, value_std;
  int ret_s21 = s21_sscanf("A", "%c", &value_s21);
  int ret_std = sscanf("A", "%c", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value_s21, value_std);
}
END_TEST

// Тест для октального числа
START_TEST(test_sscanf_octal) {
  unsigned int value_s21, value_std;
  int ret_s21 = s21_sscanf("0123", "%o", &value_s21);
  int ret_std = sscanf("0123", "%o", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_uint_eq(value_s21, value_std);
}
END_TEST

// Тест для указателя
START_TEST(test_sscanf_pointer) {
  void *value_s21, *value_std;
  int ret_s21 = s21_sscanf("0x7ffeefbff618", "%p", &value_s21);
  int ret_std = sscanf("0x7ffeefbff618", "%p", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_ptr_eq(value_s21, value_std);
}
END_TEST

// Тест для флагов
START_TEST(test_sscanf_flags) {
  int value_s21, value_std;
  int ret_s21 = s21_sscanf("-123", "%d", &value_s21);
  int ret_std = sscanf("-123", "%d", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value_s21, value_std);
}
END_TEST

// Тест для ширины
START_TEST(test_sscanf_width) {
  char str_s21[10], str_std[10];
  int ret_s21 = s21_sscanf("hello", "%3s", str_s21);
  int ret_std = sscanf("hello", "%3s", str_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_str_eq(str_s21, str_std);
}
END_TEST

START_TEST(test_sscanf_supressor) {
  int int_s21_1, int_s21_2, int_std_1, int_std_2;
  int ret_s21 = s21_sscanf("123 456 789", "%*d %d %d", &int_s21_1, &int_s21_2);
  int ret_std = sscanf("123 456 789", "%*d %d %d", &int_std_1, &int_std_2);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(int_s21_1, int_std_1);
  ck_assert_int_eq(int_s21_2, int_std_2);
}
END_TEST

// Тест для точности
START_TEST(test_sscanf_precision) {
  double value_s21, value_std;
  int ret_s21 = s21_sscanf("123.456789", "%lf", &value_s21);
  int ret_std = sscanf("123.456789", "%lf", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_double_eq(value_s21, value_std);
}
END_TEST

// Тест для длины
START_TEST(test_sscanf_length) {
  long int value_s21, value_std;
  int ret_s21 = s21_sscanf("1234567890", "%ld", &value_s21);
  int ret_std = sscanf("1234567890", "%ld", &value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value_s21, value_std);
}
END_TEST

// Тест для комбинированного формата
START_TEST(test_sscanf_combined) {
  int ivalue_s21, ivalue_std;
  double dvalue_s21, dvalue_std;
  char str_s21[100], str_std[100];
  int ret_s21, ret_std;
  ret_s21 = s21_sscanf("123 456.789 Hello", "%d %lf %99s", &ivalue_s21,
                       &dvalue_s21, str_s21);
  ret_std = sscanf("123 456.789 Hello", "%d %lf %99s", &ivalue_std, &dvalue_std,
                   str_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(ivalue_s21, ivalue_std);
  ck_assert_double_eq(dvalue_s21, dvalue_std);
  ck_assert_str_eq(str_s21, str_std);
}
END_TEST

// Тесты для функции s21_to_upper
START_TEST(test_s21_to_upper) {
  char *result;

  result = (char *)s21_to_upper("hello");
  ck_assert_str_eq(result, "HELLO");
  free(result);

  result = (char *)s21_to_upper("Привет");
  ck_assert_str_eq(result, "ПРИВЕТ");
  free(result);

  result = (char *)s21_to_upper("HeLLo WoRLd");
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);

  result = (char *)s21_to_upper("123");
  ck_assert_str_eq(result, "123");
  free(result);

  result = (char *)s21_to_upper("");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

// Тесты для функции s21_to_lower
START_TEST(test_s21_to_lower) {
  char *result;

  result = (char *)s21_to_lower("HELLO");
  ck_assert_str_eq(result, "hello");
  free(result);

  result = (char *)s21_to_lower("HeLLo WoRLd");
  ck_assert_str_eq(result, "hello world");
  free(result);

  result = (char *)s21_to_lower("123");
  ck_assert_str_eq(result, "123");
  free(result);

  result = (char *)s21_to_lower("");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

// Тесты для функции s21_insert
START_TEST(test_s21_insert) {
  char *result;

  result = (char *)s21_insert("Hello World", " beautiful", 5);
  ck_assert_str_eq(result, "Hello beautiful World");
  free(result);

  result = (char *)s21_insert("Test", "123", 0);
  ck_assert_str_eq(result, "123Test");
  free(result);

  result = (char *)s21_insert("Test", "456", 4);
  ck_assert_str_eq(result, "Test456");
  free(result);

  result = (char *)s21_insert("InsertHere", "", 6);
  ck_assert_str_eq(result, "InsertHere");
  free(result);
}
END_TEST

// Тесты для функции s21_trim
START_TEST(test_s21_trim) {
  char *result;

  result = (char *)s21_trim("   Hello, World!   ", " ");
  ck_assert_str_eq(result, "Hello, World!");
  free(result);

  result = (char *)s21_trim("   Hello, World!   ", "");
  ck_assert_str_eq(result, "Hello, World!");
  free(result);

  result = (char *)s21_trim("   Hello, World!   ", s21_NULL);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);

  result = (char *)s21_trim("###Hello###", "#");
  ck_assert_str_eq(result, "Hello");
  free(result);

  result = (char *)s21_trim("   TrimMe   ", " ");
  ck_assert_str_eq(result, "TrimMe");
  free(result);

  result = (char *)s21_trim("NoTrimNeeded", " ");
  ck_assert_str_eq(result, "NoTrimNeeded");
  free(result);
}
END_TEST

// Создание тестовых кейсов и наборов
Suite *s21_string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_string");

  // Создание тестового кейса
  tc_core = tcase_create("Core");

  // Добавление тестовых функций в тестовый кейс
  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_string);
  tcase_add_test(tc_core, test_integer);
  tcase_add_test(tc_core, test_unsigned);
  tcase_add_test(tc_core, test_short);
  tcase_add_test(tc_core, test_float);
  tcase_add_test(tc_core, test_o);
  tcase_add_test(tc_core, test_o_prefix);
  tcase_add_test(tc_core, test_pointer);
  tcase_add_test(tc_core, test_scientific);
  tcase_add_test(tc_core, test_g_format);
  tcase_add_test(tc_core, test_G_format);
  tcase_add_test(tc_core, test_character);
  tcase_add_test(tc_core, test_string_left);
  tcase_add_test(tc_core, test_zero_padded);
  tcase_add_test(tc_core, test_left_aligned);
  tcase_add_test(tc_core, test_sign);
  tcase_add_test(tc_core, test_space);
  tcase_add_test(tc_core, test_alternate);
  tcase_add_test(tc_core, test_width);
  tcase_add_test(tc_core, test_precision);
  tcase_add_test(tc_core, test_big_number);
  tcase_add_test(tc_core, test_complex_format);
  tcase_add_test(tc_core, test_sscanf_int);
  tcase_add_test(tc_core, test_sscanf_string);
  tcase_add_test(tc_core, test_sscanf_float);
  tcase_add_test(tc_core, test_sscanf_hex);
  tcase_add_test(tc_core, test_sscanf_char);
  tcase_add_test(tc_core, test_sscanf_octal);
  tcase_add_test(tc_core, s21_sprintf_prc_test);
  tcase_add_test(tc_core, test_sscanf_pointer);
  tcase_add_test(tc_core, test_sscanf_flags);
  tcase_add_test(tc_core, test_sscanf_width);
  tcase_add_test(tc_core, test_sscanf_supressor);
  tcase_add_test(tc_core, test_sscanf_precision);
  tcase_add_test(tc_core, test_sscanf_length);
  tcase_add_test(tc_core, test_sscanf_combined);
  tcase_add_test(tc_core, test_s21_to_upper);
  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_insert);
  tcase_add_test(tc_core, test_s21_trim);

  // Добавление тестового кейса в тестовый набор
  suite_add_tcase(s, tc_core);

  return s;
}

// Основная функция для запуска тестов
int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(s21_string_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  printf("%s\n", (number_failed == 0) ? "EXIT_SUCCESS" : "EXIT_FAILURE");

  return 0;
}