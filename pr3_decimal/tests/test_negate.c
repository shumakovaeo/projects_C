#include "tests.h"

START_TEST(test_negate_1) {
  // 100 -> -100
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 100;

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_negate_2) {
  // -429496729 -> 429496729
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0x19999999;
  set_sign(&value, 1);

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x19999999);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_negate_3) {
  // 1000.0000 -> -1000.0000
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 10000000;
  set_scale(&value, 4);

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 10000000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 4);
}
END_TEST

START_TEST(test_negate_4) {
  // 0 -> -0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0;

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_negate_5) {
  // -0.00 -> 0
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0;
  set_scale(&value, 2);
  set_sign(&value, 1);

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 2);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_negate_6) {
  //-> -79228162514264337593543950335
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 0xFFFFFFFF;
  value.bits[1] = 0xFFFFFFFF;
  value.bits[2] = 0xFFFFFFFF;

  int code = s21_negate(value, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFF);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_negate_7) {
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123;
  set_scale(&value, 29);

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, 1);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_negate_8) {
  s21_decimal value = {0};
  s21_decimal result = {0};

  value.bits[0] = 123;
  set_scale(&value, -3);

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, 1);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_negate_9) {
  s21_decimal value = {0};
  value.bits[0] = 123;

  int code = s21_negate(value, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *s21_test_negate(void) {
  Suite *s = suite_create("S21_NEGATE");
  TCase *tc = tcase_create("s21_negate");

  tcase_add_test(tc, test_negate_1);
  tcase_add_test(tc, test_negate_2);
  tcase_add_test(tc, test_negate_3);
  tcase_add_test(tc, test_negate_4);
  tcase_add_test(tc, test_negate_5);
  tcase_add_test(tc, test_negate_6);
  // коды ошибок
  // 1 — ошибка конвертации
  tcase_add_test(tc, test_negate_7);
  tcase_add_test(tc, test_negate_8);
  tcase_add_test(tc, test_negate_9);

  suite_add_tcase(s, tc);
  return s;
}