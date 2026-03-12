
#include "string_test.h"

START_TEST(test_s21_strstr_found) {
  const char *haystack = "hello world";
  const char *needle = "world";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_not_found) {
  const char *haystack = "hello";
  const char *needle = "xyz";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_empty_needle) {
  const char *haystack = "hello";
  const char *needle = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite *suite_s21_strstr() {
  Suite *s = suite_create("s21_strstr");
  TCase *tc = tcase_create("s21_strstr");
  tcase_add_test(tc, test_s21_strstr_found);
  tcase_add_test(tc, test_s21_strstr_not_found);
  tcase_add_test(tc, test_s21_strstr_empty_needle);
  suite_add_tcase(s, tc);
  return s;
}
