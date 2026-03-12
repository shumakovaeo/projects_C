
#include "string_test.h"

START_TEST(test_s21_strlen_normal) {
  const char *str = "hello world";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_empty) {
  const char *str = "";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_single) {
  const char *str = "a";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *suite_s21_strlen() {
  Suite *s = suite_create("s21_strlen");
  TCase *tc = tcase_create("s21_strlen");
  tcase_add_test(tc, test_s21_strlen_normal);
  tcase_add_test(tc, test_s21_strlen_empty);
  tcase_add_test(tc, test_s21_strlen_single);
  suite_add_tcase(s, tc);
  return s;
}
