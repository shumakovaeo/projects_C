
#include "string_test.h"

START_TEST(test_s21_strcspn_normal) {
  const char *str1 = "hello world";
  const char *str2 = " ";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_no_match) {
  const char *str1 = "hello";
  const char *str2 = "xyz";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_empty_str2) {
  const char *str1 = "hello";
  const char *str2 = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

Suite *suite_s21_strcspn() {
  Suite *s = suite_create("s21_strcspn");
  TCase *tc = tcase_create("s21_strcspn");
  tcase_add_test(tc, test_s21_strcspn_normal);
  tcase_add_test(tc, test_s21_strcspn_no_match);
  tcase_add_test(tc, test_s21_strcspn_empty_str2);
  suite_add_tcase(s, tc);
  return s;
}
