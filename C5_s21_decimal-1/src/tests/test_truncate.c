#include "test_decimal.h"

START_TEST(test_truncate_no_fraction) {
  s21_decimal value = {
      {123456789, 0, 0,
       0x00000000}};  // Целое число без дробной части (123456789)
  s21_decimal expected = {
      {123456789, 0, 0, 0}};  // Ожидаемое число без изменений (123456789)
  s21_decimal result;

  int error_code = s21_truncate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_truncate_with_fraction) {
  s21_decimal value = {{123456789, 0, 0, 0x00020000}};   // 1234567.89
  s21_decimal expected = {{1234567, 0, 0, 0x00000000}};  // 1234567
  s21_decimal result;

  int error_code = s21_truncate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_truncate_with_fraction_2) {
  s21_decimal value = {{123456789, 0, 0, 0x00080000}};  // 1.23456789
  s21_decimal expected = {{1, 0, 0, 0x00000000}};       // 1
  s21_decimal result;

  int error_code = s21_truncate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_truncate_negative_number) {
  s21_decimal value = {
      {987654321, 0, 0, 0x80000000}};  // Отрицательное целое число (-987654321)
  s21_decimal expected = {
      {987654321, 0, 0, 0x80000000}};  // Ожидаемое отрицательное число без
                                       // изменений (-987654321)
  s21_decimal result;

  int error_code = s21_truncate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_truncate_with_fraction_negative) {
  s21_decimal value = {{123456789, 0, 0, 0x80020000}};   // -1234567.89
  s21_decimal expected = {{1234567, 0, 0, 0x80000000}};  // -1234567
  s21_decimal result;

  int error_code = s21_truncate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_truncate_with_fraction_negative_2) {
  s21_decimal value = {{123456789, 0, 0, 0x80080000}};  // -1.23456789
  s21_decimal expected = {{1, 0, 0, 0x80000000}};       // -1
  s21_decimal result;

  int error_code = s21_truncate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_truncate_large_scale) {
  s21_decimal value = {
      {1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal expected = {{0, 0, 0, 0x00000000}};  // 0
  s21_decimal result;

  int error_code = s21_truncate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_truncate_null_pointer) {
  s21_decimal value = {
      {123456789, 0, 0,
       0x00180000}};  // Любое число с дробной частью (например,
                      // 0.000000000000000000123456789)

  int error_code =
      s21_truncate(value, NULL);  // Передаем NULL как указатель на результат

  ck_assert_int_eq(error_code, 1);  // Ожидаем код ошибки 1
}
END_TEST

START_TEST(test_truncate_zero_with_large_negative_bit) {
  // Значение нуля с масштабом 28 и отрицательным знаком
  s21_decimal value = {{0b00000000000000000000000000000000,
                        0b00000000000000000000000000000000,
                        0b00000000000000000000000000000000,
                        0b10000000000111000000000000000000}};  // 0

  // Ожидаемое значение после усечения: ноль остается нулем, знак отрицательный
  s21_decimal expected = {{0b00000000000000000000000000000000,
                           0b00000000000000000000000000000000,
                           0b00000000000000000000000000000000,
                           0b10000000000000000000000000000000}};  // 0

  s21_decimal result;

  int error_code = s21_truncate(value, &result);

  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_truncate_custom_values) {
  s21_decimal value1 = {{1, 2, 3, 917504}};     // 553402.32229718589441
  s21_decimal expected1 = {{553402, 0, 0, 0}};  // 553402
  s21_decimal result1;
  int error_code1 = s21_truncate(value1, &result1);
  ck_assert_int_eq(error_code1, 0);
  ck_assert_mem_eq(&result1, &expected1, sizeof(s21_decimal));

  s21_decimal value2 = {{1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal expected2 = {{553402, 0, 0, -2147483648}};  // -553402
  s21_decimal result2;
  int error_code2 = s21_truncate(value2, &result2);
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));

  s21_decimal value3 = {
      {33, 2, 3000, -2146107392}};  // -55.340232221137244782625
  s21_decimal expected3 = {{55, 0, 0, -2147483648}};  // -55
  s21_decimal result3;
  int error_code3 = s21_truncate(value3, &result3);
  ck_assert_int_eq(error_code3, 0);
  ck_assert_mem_eq(&result3, &expected3, sizeof(s21_decimal));

  s21_decimal value4 = {{10, 100, 3, 1376256}};  // 0.055340232650625384458
  s21_decimal expected4 = {{0, 0, 0, 0}};        // 0
  s21_decimal result4;
  int error_code4 = s21_truncate(value4, &result4);
  ck_assert_int_eq(error_code4, 0);
  ck_assert_mem_eq(&result4, &expected4, sizeof(s21_decimal));

  s21_decimal value5 = {{16, 100, 3, 851968}};   // 5534023.2650625384464
  s21_decimal expected5 = {{5534023, 0, 0, 0}};  // 5534023
  s21_decimal result5;
  int error_code5 = s21_truncate(value5, &result5);
  ck_assert_int_eq(error_code5, 0);
  ck_assert_mem_eq(&result5, &expected5, sizeof(s21_decimal));

  s21_decimal value6 = {
      {32444, 100, 343253, -2145976320}};  // -63.31900243533454217608892
  s21_decimal expected6 = {{63, 0, 0, -2147483648}};  // -63
  s21_decimal result6;
  int error_code6 = s21_truncate(value6, &result6);
  ck_assert_int_eq(error_code6, 0);
  ck_assert_mem_eq(&result6, &expected6, sizeof(s21_decimal));

  s21_decimal value7 = {{0, 0, 0, 851968}};  // 0.0000000000000
  s21_decimal expected7 = {{0, 0, 0, 0}};    // 0
  s21_decimal result7;
  int error_code7 = s21_truncate(value7, &result7);
  ck_assert_int_eq(error_code7, 0);
  ck_assert_mem_eq(&result7, &expected7, sizeof(s21_decimal));

  s21_decimal value8 = {{1, 1, 1, 655360}};         // 1844674407.8004518913
  s21_decimal expected8 = {{1844674407, 0, 0, 0}};  // 1844674407
  s21_decimal result8;
  int error_code8 = s21_truncate(value8, &result8);
  ck_assert_int_eq(error_code8, 0);
  ck_assert_mem_eq(&result8, &expected8, sizeof(s21_decimal));

  s21_decimal value10 = {{1, 10, 1, -2146500608}};  // -18446.744116659224577
  s21_decimal expected10 = {{18446, 0, 0, -2147483648}};  // -18446
  s21_decimal result10;
  int error_code10 = s21_truncate(value10, &result10);
  ck_assert_int_eq(error_code10, 0);
  ck_assert_mem_eq(&result10, &expected10, sizeof(s21_decimal));

  s21_decimal value12 = {{1, 1, 1, 917504}};     // 184467.44078004518913
  s21_decimal expected12 = {{184467, 0, 0, 0}};  // 184467
  s21_decimal result12;
  int error_code12 = s21_truncate(value12, &result12);
  ck_assert_int_eq(error_code12, 0);
  ck_assert_mem_eq(&result12, &expected12, sizeof(s21_decimal));

  s21_decimal value14 = {{1, 15, 1, 655360}};        // 1844674413.8134061057
  s21_decimal expected14 = {{1844674413, 0, 0, 0}};  // 1844674413
  s21_decimal result14;
  int error_code14 = s21_truncate(value14, &result14);
  ck_assert_int_eq(error_code14, 0);
  ck_assert_mem_eq(&result14, &expected14, sizeof(s21_decimal));

  s21_decimal value9 = {{1, 1, 1, 65536}};  // 1844674407800451891.3
  s21_decimal expected9 = {
      {-1288490189, 429496729, 0, 0}};  // 1844674407800451891
  s21_decimal result9;
  int error_code9 = s21_truncate(value9, &result9);
  ck_assert_int_eq(error_code9, 0);
  ck_assert_mem_eq(&result9, &expected9, sizeof(s21_decimal));

  s21_decimal value11 = {{3, 2, 1, 524288}};          // 184467440822.99486211
  s21_decimal expected11 = {{-216152906, 42, 0, 0}};  // 184467440822
  s21_decimal result11;
  int error_code11 = s21_truncate(value11, &result11);
  ck_assert_int_eq(error_code11, 0);
  ck_assert_mem_eq(&result11, &expected11, sizeof(s21_decimal));

  s21_decimal value13 = {{24, 1, 1, -2147418112}};  // -1844674407800451893.6
  s21_decimal expected13 = {
      {-1288490187, 429496729, 0, -2147483648}};  // -1844674407800451893
  s21_decimal result13;
  int error_code13 = s21_truncate(value13, &result13);
  ck_assert_int_eq(error_code13, 0);
  ck_assert_mem_eq(&result13, &expected13, sizeof(s21_decimal));

  s21_decimal value15 = {{1, 1, 1, -2147418112}};  // -1844674407800451891.3
  s21_decimal expected15 = {
      {-1288490189, 429496729, 0, -2147483648}};  // -1844674407800451891
  s21_decimal result15;
  int error_code15 = s21_truncate(value15, &result15);
  ck_assert_int_eq(error_code15, 0);
  ck_assert_mem_eq(&result15, &expected15, sizeof(s21_decimal));

  s21_decimal value22 = {{1, 2, 3, 655360}};         // 5534023222.9718589441
  s21_decimal expected22 = {{1239055926, 1, 0, 0}};  // 5534023222
  s21_decimal result22;
  int error_code22 = s21_truncate(value22, &result22);
  ck_assert_int_eq(error_code22, 0);
  ck_assert_mem_eq(&result22, &expected22, sizeof(s21_decimal));

  s21_decimal value25 = {{1, 2, 3, -2146828288}};  // -5534023222.9718589441
  s21_decimal expected25 = {{1239055926, 1, 0, -2147483648}};  // -5534023222
  s21_decimal result25;
  int error_code25 = s21_truncate(value25, &result25);
  ck_assert_int_eq(error_code25, 0);
  ck_assert_mem_eq(&result25, &expected25, sizeof(s21_decimal));

  s21_decimal value26 = {{3, 2, 1, -2146959360}};  // -184467440822.99486211
  s21_decimal expected26 = {{-216152906, 42, 0, -2147483648}};  // -184467440822
  s21_decimal result26;
  int error_code26 = s21_truncate(value26, &result26);
  ck_assert_int_eq(error_code26, 0);
  ck_assert_mem_eq(&result26, &expected26, sizeof(s21_decimal));

  s21_decimal value18 = {{1, 0, 1, 917504}};     // 184467.44073709551617
  s21_decimal expected18 = {{184467, 0, 0, 0}};  // 184467
  s21_decimal result18;
  int error_code18 = s21_truncate(value18, &result18);
  ck_assert_int_eq(error_code18, 0);
  ck_assert_mem_eq(&result18, &expected18, sizeof(s21_decimal));

  s21_decimal value20 = {{1, 1, 1, 983040}};    // 18446.744078004518913
  s21_decimal expected20 = {{18446, 0, 0, 0}};  // 18446
  s21_decimal result20;
  int error_code20 = s21_truncate(value20, &result20);
  ck_assert_int_eq(error_code20, 0);
  ck_assert_mem_eq(&result20, &expected20, sizeof(s21_decimal));

  s21_decimal value21 = {{1, 1, 1, -2146500608}};  // -18446.744078004518913
  s21_decimal expected21 = {{18446, 0, 0, -2147483648}};  // -18446
  s21_decimal result21;
  int error_code21 = s21_truncate(value21, &result21);
  ck_assert_int_eq(error_code21, 0);
  ck_assert_mem_eq(&result21, &expected21, sizeof(s21_decimal));

  s21_decimal value24 = {{3, 2, 1, -2146828288}};  // -1844674408.2299486211
  s21_decimal expected24 = {{1844674408, 0, 0, -2147483648}};  // -1844674408
  s21_decimal result24;
  int error_code24 = s21_truncate(value24, &result24);
  ck_assert_int_eq(error_code24, 0);
  ck_assert_mem_eq(&result24, &expected24, sizeof(s21_decimal));

  s21_decimal value27 = {{10, 2, 3, -2146566144}};  // -553402.32229718589450
  s21_decimal expected27 = {{553402, 0, 0, -2147483648}};  // -553402
  s21_decimal result27;
  int error_code27 = s21_truncate(value27, &result27);
  ck_assert_int_eq(error_code27, 0);
  ck_assert_mem_eq(&result27, &expected27, sizeof(s21_decimal));

  s21_decimal value28 = {{1, 2, 3, 917504}};     // 553402.32229718589441
  s21_decimal expected28 = {{553402, 0, 0, 0}};  // 553402
  s21_decimal result28;
  int error_code28 = s21_truncate(value28, &result28);
  ck_assert_int_eq(error_code28, 0);
  ck_assert_mem_eq(&result28, &expected28, sizeof(s21_decimal));

  s21_decimal value29 = {{1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal expected29 = {{553402, 0, 0, -2147483648}};  // -553402
  s21_decimal result29;
  int error_code29 = s21_truncate(value29, &result29);
  ck_assert_int_eq(error_code29, 0);
  ck_assert_mem_eq(&result29, &expected29, sizeof(s21_decimal));

  s21_decimal value30 = {{10, 0, 0, 0}};     // 10
  s21_decimal expected30 = {{10, 0, 0, 0}};  // 10
  s21_decimal result30;
  int error_code30 = s21_truncate(value30, &result30);
  ck_assert_int_eq(error_code30, 0);
  ck_assert_mem_eq(&result30, &expected30, sizeof(s21_decimal));

  s21_decimal value31 = {{133456435, 0, 0, -2147483648}};     // -133456435
  s21_decimal expected31 = {{133456435, 0, 0, -2147483648}};  // -133456435
  s21_decimal result31;
  int error_code31 = s21_truncate(value31, &result31);
  ck_assert_int_eq(error_code31, 0);
  ck_assert_mem_eq(&result31, &expected31, sizeof(s21_decimal));

  s21_decimal value32 = {{2343453, 0, 0, -2147024896}};  // -0.2343453
  s21_decimal expected32 = {{0, 0, 0, -2147483648}};     // -0
  s21_decimal result32;
  int error_code32 = s21_truncate(value32, &result32);
  ck_assert_int_eq(error_code32, 0);
  ck_assert_mem_eq(&result32, &expected32, sizeof(s21_decimal));

  s21_decimal value33 = {{1272343, 0, 0, 262144}};  // 127.2343
  s21_decimal expected33 = {{127, 0, 0, 0}};        // 127
  s21_decimal result33;
  int error_code33 = s21_truncate(value33, &result33);
  ck_assert_int_eq(error_code33, 0);
  ck_assert_mem_eq(&result33, &expected33, sizeof(s21_decimal));
}
END_TEST

Suite *test_truncate(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[35ms21_truncate\033[0m");

  tc_core = tcase_create("truncate_tc");

  tcase_add_test(tc_core, test_truncate_no_fraction);
  tcase_add_test(tc_core, test_truncate_with_fraction);
  tcase_add_test(tc_core, test_truncate_with_fraction_2);
  tcase_add_test(tc_core, test_truncate_with_fraction_negative);
  tcase_add_test(tc_core, test_truncate_with_fraction_negative_2);
  tcase_add_test(tc_core, test_truncate_negative_number);
  tcase_add_test(tc_core, test_truncate_large_scale);
  tcase_add_test(tc_core, test_truncate_null_pointer);
  tcase_add_test(tc_core, test_truncate_zero_with_large_negative_bit);
  tcase_add_test(tc_core, test_truncate_custom_values);

  suite_add_tcase(s, tc_core);

  return s;
}
