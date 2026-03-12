
#include "string_test.h"

START_TEST(test_s21_trim_normal) {
  const char *src = "  hello  ";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_multiple_chars) {
  const char *src = "\t\n hello \n\t";
  const char *trim_chars = "\t\n ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_no_trim) {
  const char *src = "hello";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty) {
  const char *src = "";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_str_null1) {
  char *result = (char *)s21_trim(s21_NULL, "a");
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_s21_trim_str_null2) {
  char *result = (char *)s21_trim("a", s21_NULL);
  ck_assert_str_eq(result, "a");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_str_null3) {
  char *result = (char *)s21_trim(s21_NULL, s21_NULL);
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

Suite *suite_s21_trim() {
  Suite *s = suite_create("s21_trim");
  TCase *tc = tcase_create("s21_trim");
  tcase_add_test(tc, test_s21_trim_normal);
  tcase_add_test(tc, test_s21_trim_multiple_chars);
  tcase_add_test(tc, test_s21_trim_no_trim);
  tcase_add_test(tc, test_s21_trim_empty);
  tcase_add_test(tc, test_s21_trim_str_null1);
  tcase_add_test(tc, test_s21_trim_str_null2);
  tcase_add_test(tc, test_s21_trim_str_null3);
  suite_add_tcase(s, tc);
  return s;
}
