#include "tests.h"

START_TEST(test_from_decimal_to_int_1) {
  s21_decimal val = {0};
  int result = 0;

  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_2) {
  s21_decimal val = {{102085, 0, 0, 0x80000000}};
  int result = 0;

  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, -102085);
}
END_TEST

START_TEST(test_from_decimal_to_int_3) {
  s21_decimal val = {{0x7FFFFFFF, 0, 0, 0}};
  int result = 0;

  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, 2147483647);
}
END_TEST

START_TEST(test_from_decimal_to_int_4) {
  s21_decimal val = {{102085, 0, 0, 0x20000}};
  int result = 0;

  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, 1020);
}
END_TEST

START_TEST(test_from_decimal_to_int_5) {
  s21_decimal val = {0};
  val.bits[0] = 42;

  int result = 0;
  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, 42);
}
END_TEST

START_TEST(test_from_decimal_to_int_6) {
  s21_decimal val = {0};
  val.bits[0] = 1;
  val.bits[3] = 0x80000000;

  int result = 0;
  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_from_decimal_to_int_7) {
  s21_decimal val = {0};
  val.bits[0] = 0x80000000;
  val.bits[3] = 0x80000000;

  int result = 0;
  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, -2147483648);
}
END_TEST

START_TEST(test_from_decimal_to_int_8) {
  s21_decimal val = {0};
  val.bits[0] = 0xFFFFFFFF;
  val.bits[1] = 1;

  int result = 0;
  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 1);  // Ошибка переполнения
}
END_TEST

START_TEST(test_from_decimal_to_int_9) {
  s21_decimal val = {0};
  val.bits[0] = 0xFFFFFFFF;
  val.bits[1] = 1;
  val.bits[3] = 0x80000000;

  int result = 0;
  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(code, 1);  // Ошибка переполнения
}
END_TEST

START_TEST(test_from_decimal_to_int_10) {
  s21_decimal val = {0};
  val.bits[0] = 12345;
  val.bits[3] = 0x10000;

  int result = 0;
  int code = s21_from_decimal_to_int(val, &result);

  ck_assert_int_eq(result, 1234);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_11) {
  s21_decimal val = {0};
  val.bits[0] = 42;

  int code = s21_from_decimal_to_int(val, NULL);

  ck_assert_int_eq(code, 1);  // Ошибка: NULL указатель
}
END_TEST

Suite *s21_test_from_decimal_to_int(void) {
  Suite *s = suite_create("S21_FROM_DECIMAL_TO_INT");
  TCase *tc = tcase_create("s21_from_decimal_to_int");

  tcase_add_test(tc, test_from_decimal_to_int_1);
  tcase_add_test(tc, test_from_decimal_to_int_2);
  tcase_add_test(tc, test_from_decimal_to_int_3);
  tcase_add_test(tc, test_from_decimal_to_int_4);
  tcase_add_test(tc, test_from_decimal_to_int_5);
  tcase_add_test(tc, test_from_decimal_to_int_6);
  tcase_add_test(tc, test_from_decimal_to_int_7);
  tcase_add_test(tc, test_from_decimal_to_int_8);
  tcase_add_test(tc, test_from_decimal_to_int_9);
  tcase_add_test(tc, test_from_decimal_to_int_10);
  tcase_add_test(tc, test_from_decimal_to_int_11);

  suite_add_tcase(s, tc);
  return s;
}