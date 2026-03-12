#include "tests.h"

START_TEST(test_round_1) {
  // 5.4 -> 5
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 54;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 5);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_round_2) {
  // 5.5 -> 6
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 55;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 6);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_round_3) {
  // 2.1 -> 2
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 21;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_round_4) {
  // -5.4 -> -5
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 54;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 5);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_round_5) {
  // -5.5 -> -6
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 55;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 6);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_round_6) {
  // 0.4 -> 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 4;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_round_7) {
  // 0.5 -> 1
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 5;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_round_8) {
  // -0.5 -> -1
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 5;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_round_9) {
  // 4294967296.5 -> 4294967297
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x00000005;
  value.bits[1] = 0x0000000A;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0x00000001);
  ck_assert_uint_eq(result.bits[1], 0x00000001);
  ck_assert_uint_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_round_10) {
  // 123456789012345.5 -> 123456789012346
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x3C8ABABF;
  value.bits[1] = 0x000462D5;
  value.bits[2] = 0x00000000;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x860DDF7A);
  ck_assert(result.bits[1] == 0x00007048);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_round_11) {
  // 21474836480.4 -> 2147483648
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x00000004;
  value.bits[1] = 0x00000005;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);

  ck_assert(result.bits[0] == 0x80000000U);
  ck_assert(result.bits[1] == 0x00000000U);
  ck_assert(result.bits[2] == 0x00000000U);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_round_12) {
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0xAAAAAAAA;
  value.bits[1] = 0xBBBBBBBB;
  value.bits[2] = 0xCCCCCCCC;
  set_scale(&value, 0);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xAAAAAAAAU);
  ck_assert(result.bits[1] == 0xBBBBBBBBU);
  ck_assert(result.bits[2] == 0xCCCCCCCCU);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_round_13) {
  // 0.0 -> 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0;
  set_scale(&value, 5);  // 0.00000

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_round_14) {
  // 54 -> 54
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 54;

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 54);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_round_15) {
  // 0.000001 -> 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 1;
  set_scale(&value, 6);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_round_16) {
  // 123456789.00000
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x73CE2B20;
  value.bits[1] = 0x00000B3A;
  value.bits[2] = 0x00000000;
  set_scale(&value, 5);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x075BCD15);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_round_17) {
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123;
  set_scale(&value, 29);  // > 28

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_round_18) {
  // 0.0000 -> 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0;
  set_scale(&value, 4);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_round_19) {
  // -0.5 -> -1
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 5;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_round_20) {
  // -0.0 -> -0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_round_21) {
  // -0 -> -0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0;
  set_sign(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_round_22) {
  // 10.5 -> 11
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 105;
  set_scale(&value, 1);

  int code = s21_round(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 11);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_round_23) {
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 1;
  set_scale(&value, -28);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_round_24) {
  s21_decimal value = {0};
  value.bits[0] = 123;
  set_scale(&value, 1);

  int code = s21_round(value, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *s21_test_round(void) {
  Suite *s = suite_create("S21_ROUND");
  TCase *tc = tcase_create("s21_round");

  tcase_add_test(tc, test_round_1);
  tcase_add_test(tc, test_round_2);
  tcase_add_test(tc, test_round_3);
  tcase_add_test(tc, test_round_4);
  tcase_add_test(tc, test_round_5);
  tcase_add_test(tc, test_round_6);
  tcase_add_test(tc, test_round_7);
  tcase_add_test(tc, test_round_8);
  tcase_add_test(tc, test_round_9);
  tcase_add_test(tc, test_round_10);
  tcase_add_test(tc, test_round_11);
  tcase_add_test(tc, test_round_12);
  tcase_add_test(tc, test_round_13);
  tcase_add_test(tc, test_round_14);
  tcase_add_test(tc, test_round_15);
  tcase_add_test(tc, test_round_16);
  tcase_add_test(tc, test_round_18);
  tcase_add_test(tc, test_round_22);
  // sign при 0
  tcase_add_test(tc, test_round_19);
  tcase_add_test(tc, test_round_20);
  tcase_add_test(tc, test_round_21);
  // коды ошибок
  // 1 — ошибка конвертации
  tcase_add_test(tc, test_round_17);
  tcase_add_test(tc, test_round_23);
  tcase_add_test(tc, test_round_24);

  suite_add_tcase(s, tc);
  return s;
}