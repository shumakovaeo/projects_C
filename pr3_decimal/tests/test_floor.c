#include "tests.h"

START_TEST(test_floor_1) {
  // 5.9 -> 5
  s21_decimal value = {0};
  s21_decimal result = {0};
  s21_decimal expected = {0};

  value.bits[0] = 59;
  set_scale(&value, 1);
  expected.bits[0] = 5;

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_floor_2) {
  // 2.1 -> 2
  s21_decimal value = {0};
  s21_decimal result = {0};
  s21_decimal expected = {0};

  value.bits[0] = 21;
  set_scale(&value, 1);
  expected.bits[0] = 2;

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_floor_3) {
  // 7.0 -> 7
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 70;
  set_scale(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 7);
}
END_TEST

START_TEST(test_floor_4) {
  // -5.9 -> -6
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 59;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 6);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_floor_5) {
  // -2.1 -> -3
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 21;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_floor_6) {
  // 0.5 -> 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 5;
  set_scale(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_floor_7) {
  // -0.5 -> -1
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 5;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_floor_8) {
  // 123456.789 -> 123456
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123456789;
  set_scale(&value, 3);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 123456);
}
END_TEST

START_TEST(test_floor_9) {
  // -123456.789 -> -123457
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123456789;
  set_scale(&value, 3);
  set_sign(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 123457);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_floor_10) {
  // 42 -> 42
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 42;
  set_scale(&value, 0);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 42);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_floor_11) {
  // 429496732.9 -> 429496732
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x00000021;
  value.bits[1] = 0x00000001;
  set_scale(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0x1999999C);
  ck_assert_uint_eq(result.bits[1], 0x00000000);
  ck_assert_uint_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_floor_12) {
  // 0.000001 -> 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 1;
  set_scale(&value, 6);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_floor_13) {
  // -0.000001 -> -1
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 1;
  set_scale(&value, 6);
  set_sign(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_floor_14) {
  // 4294967295.5 -> 4294967295
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0xFFFFFFFB;
  value.bits[1] = 0x00000009;
  set_scale(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFF);
}
END_TEST

START_TEST(test_floor_15) {
  // -0.0 -> -0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0;
  set_scale(&value, 1);
  set_sign(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_floor_16) {
  // 1.23456789 -> 1
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123456789;
  set_scale(&value, 8);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 1);
}
END_TEST

START_TEST(test_floor_17) {
  //-123456789.000001 -> -123456790
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x860DAF41;
  value.bits[1] = 0x00007048;
  set_scale(&value, 6);
  set_sign(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0x075BCD16);
  ck_assert_uint_eq(result.bits[1], 0x00000000);
  ck_assert_uint_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_floor_18) {
  //-12.345 -> -13
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 12345;
  set_scale(&value, 3);
  set_sign(&value, 1);

  int code = s21_floor(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x0000000D);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_floor_19) {
  // scale > 28
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123;
  set_scale(&value, 29);

  int code = s21_floor(value, &result);
  ck_assert_int_eq(code, 1);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
}
END_TEST

START_TEST(test_floor_20) {
  // scale < 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123;
  set_scale(&value, -3);

  int code = s21_floor(value, &result);
  ck_assert_int_eq(code, 1);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
}
END_TEST

START_TEST(test_floor_21) {
  s21_decimal value = {0};
  value.bits[0] = 123;
  set_scale(&value, 1);

  int code = s21_floor(value, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *s21_test_floor(void) {
  Suite *s = suite_create("S21_FLOOR");
  TCase *tc = tcase_create("s21_floor");

  tcase_add_test(tc, test_floor_1);
  tcase_add_test(tc, test_floor_2);
  tcase_add_test(tc, test_floor_3);
  tcase_add_test(tc, test_floor_4);
  tcase_add_test(tc, test_floor_5);
  tcase_add_test(tc, test_floor_6);
  tcase_add_test(tc, test_floor_7);
  tcase_add_test(tc, test_floor_8);
  tcase_add_test(tc, test_floor_9);
  tcase_add_test(tc, test_floor_10);
  tcase_add_test(tc, test_floor_11);
  tcase_add_test(tc, test_floor_12);
  tcase_add_test(tc, test_floor_13);
  tcase_add_test(tc, test_floor_14);
  tcase_add_test(tc, test_floor_15);
  tcase_add_test(tc, test_floor_16);
  tcase_add_test(tc, test_floor_17);
  tcase_add_test(tc, test_floor_18);

  // коды ошибок
  // 1 — ошибка конвертации
  tcase_add_test(tc, test_floor_19);
  tcase_add_test(tc, test_floor_20);
  tcase_add_test(tc, test_floor_21);

  suite_add_tcase(s, tc);
  return s;
}