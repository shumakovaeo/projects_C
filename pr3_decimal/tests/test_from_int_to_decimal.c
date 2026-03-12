#include "tests.h"

START_TEST(test_from_int_to_decimal_1) {
  s21_decimal res = {0};
  int val = 0;

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(res.bits[i], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_2) {
  s21_decimal res = {0};
  int val = -102085;

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  for (int i = 1; i < 3; i++) ck_assert_int_eq(res.bits[i], 0);
  ck_assert_int_eq(res.bits[0], 102085);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_from_int_to_decimal_3) {
  s21_decimal res = {0};
  int val = 2147483647;

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  for (int i = 1; i < 4; i++) ck_assert_int_eq(res.bits[i], 0);
  ck_assert_int_eq(res.bits[0], 0x7FFFFFFF);
}
END_TEST

START_TEST(test_from_int_to_decimal_4) {
  s21_decimal res = {0};
  int val = -2147483648;  // INT_MIN

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 0x80000000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_from_int_to_decimal_5) {
  s21_decimal res = {0};
  int val = 42;

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 42);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_6) {
  s21_decimal res = {0};
  int val = -1;

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_from_int_to_decimal_7) {
  s21_decimal res = {0};
  int val = 1000000;

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 1000000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_8) {
  s21_decimal res = {0};
  int val = -999999;

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 999999);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_from_int_to_decimal_9) {
  s21_decimal res = {0};
  int val = 0x40000000;

  int code = s21_from_int_to_decimal(val, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 0x40000000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_10) {
  int val = 42;
  int code = s21_from_int_to_decimal(val, NULL);

  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *s21_test_from_int_to_decimal(void) {
  Suite *s = suite_create("S21_FROM_INT_TO_DECIMAL");
  TCase *tc = tcase_create("s21_from_int_to_decimal");

  tcase_add_test(tc, test_from_int_to_decimal_1);
  tcase_add_test(tc, test_from_int_to_decimal_2);
  tcase_add_test(tc, test_from_int_to_decimal_3);
  tcase_add_test(tc, test_from_int_to_decimal_4);
  tcase_add_test(tc, test_from_int_to_decimal_5);
  tcase_add_test(tc, test_from_int_to_decimal_6);
  tcase_add_test(tc, test_from_int_to_decimal_7);
  tcase_add_test(tc, test_from_int_to_decimal_8);
  tcase_add_test(tc, test_from_int_to_decimal_9);
  tcase_add_test(tc, test_from_int_to_decimal_10);

  suite_add_tcase(s, tc);
  return s;
}