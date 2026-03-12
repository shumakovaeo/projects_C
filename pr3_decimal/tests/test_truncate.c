#include "tests.h"

START_TEST(test_truncate_1) {
  // 5.9 -> 5
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 59;
  set_scale(&value, 1);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_truncate_2) {
  // 429496729.5 -> 429496729
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0xFFFFFFFF;
  set_scale(&value, 1);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x19999999);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_3) {
  // 65536.9999 -> 65536
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 655369999;
  set_scale(&value, 4);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 65536);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_4) {
  // 1000.0000 -> 1000
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 10000000;
  set_scale(&value, 4);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 1000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_5) {
  // -100.9 -> -100
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 1009;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_truncate_6) {
  // 4294967296.5 -> 4294967296
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x00000005;
  value.bits[1] = 0x0000000A;
  set_scale(&value, 1);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000001);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_7) {
  // 999999999.000001 -> 999999999
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0xA4B73DC1;
  value.bits[1] = 0x00038D7E;
  set_scale(&value, 6);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x3B9AC9FF);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_8) {
  // 50000.999 -> 50000
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 50000999;
  set_scale(&value, 3);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 50000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_9) {
  // 123456789.10000 -> 123456789
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x73CE5230;
  value.bits[1] = 0x00000B3A;
  value.bits[2] = 0x00000000;
  set_scale(&value, 5);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x075BCD15);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_10) {
  // 18446744073709551615.1 -> 18446744073709551615
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0xFFFFFFF7;
  value.bits[1] = 0xFFFFFFFF;
  value.bits[2] = 0x00000009;
  set_scale(&value, 1);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFF);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_11) {
  // 0.999999999 -> 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 999999999;
  set_scale(&value, 9);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_12) {
  // 7922816251426433759354395033
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x99999999;
  value.bits[1] = 0x99999999;
  value.bits[2] = 0x19999999;
  set_scale(&value, 0);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x99999999);
  ck_assert(result.bits[1] == 0x99999999);
  ck_assert(result.bits[2] == 0x19999999);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_13) {
  // 7922816251426433759354.3950335 -> 7922816251426433759354
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0xFFFFFFFF;
  value.bits[1] = 0xFFFFFFFF;
  value.bits[2] = 0xFFFFFFFF;
  set_scale(&value, 7);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xF485787A);
  ck_assert(result.bits[1] == 0x7F29ABCA);
  ck_assert(result.bits[2] == 0x000001AD);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_14) {
  // -123456.789 -> -123456
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123456789;
  set_scale(&value, 3);
  set_sign(&value, 1);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 123456);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_truncate_15) {
  // -0.00000 -> -0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0;
  set_scale(&value, 5);
  set_sign(&value, 1);

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_truncate_16) {
  // 123456789.00000
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x73CE2B20;
  value.bits[1] = 0x00000B3A;
  value.bits[2] = 0x00000000;
  set_scale(&value, 5);

  int code = s21_truncate(value, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x075BCD15);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_truncate_17) {
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123;
  set_scale(&value, 29);

  int code = s21_truncate(value, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_truncate_18) {
  // 7.9228162514264337593543950335 -> 7
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0xFFFFFFFF;
  value.bits[1] = 0xFFFFFFFF;
  value.bits[2] = 0xFFFFFFFF;
  set_scale(&value, 28);

  int code = s21_truncate(value, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000007);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_truncate_19) {
  // -5 -> -5
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 5;
  value.bits[1] = 0x00000000;
  value.bits[2] = 0x00000000;
  set_scale(&value, 0);
  set_sign(&value, 1);

  int code = s21_truncate(value, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000005);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_truncate_20) {
  s21_decimal value = {0};
  value.bits[0] = 123;
  set_scale(&value, 1);

  int code = s21_truncate(value, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *s21_test_truncate(void) {
  Suite *s = suite_create("S21_TRUNCATE");
  TCase *tc = tcase_create("s21_truncate");

  tcase_add_test(tc, test_truncate_1);
  tcase_add_test(tc, test_truncate_2);
  tcase_add_test(tc, test_truncate_3);
  tcase_add_test(tc, test_truncate_4);
  tcase_add_test(tc, test_truncate_5);
  tcase_add_test(tc, test_truncate_6);
  tcase_add_test(tc, test_truncate_7);
  tcase_add_test(tc, test_truncate_8);
  tcase_add_test(tc, test_truncate_9);
  tcase_add_test(tc, test_truncate_10);
  tcase_add_test(tc, test_truncate_11);
  tcase_add_test(tc, test_truncate_12);
  tcase_add_test(tc, test_truncate_13);
  tcase_add_test(tc, test_truncate_14);
  tcase_add_test(tc, test_truncate_15);
  tcase_add_test(tc, test_truncate_16);
  tcase_add_test(tc, test_truncate_18);
  tcase_add_test(tc, test_truncate_19);

  // коды ошибок
  // 1 — ошибка конвертации
  tcase_add_test(tc, test_truncate_17);
  tcase_add_test(tc, test_truncate_20);

  suite_add_tcase(s, tc);
  return s;
}