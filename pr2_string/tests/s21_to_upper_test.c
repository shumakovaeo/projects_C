
#include "string_test.h"

START_TEST(test_s21_to_upper_normal) {
  const char *str = "hello";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO");
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_mixed) {
  const char *str = "HeLLo WoRlD";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_empty) {
  const char *str = "";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_lower_str_null) {
  char *result = (char *)s21_to_upper(s21_NULL);
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_to_lower_empty_string) {
  char *result = (char *)s21_to_upper("");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_lower_no_upper) {
  char *result = (char *)s21_to_upper("hello world");
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST

START_TEST(test_to_lower_with_upper) {
  char *result = (char *)s21_to_upper("HELLO WORLD");
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST

Suite *suite_s21_to_upper() {
  Suite *s = suite_create("s21_to_upper");
  TCase *tc = tcase_create("s21_to_upper");
  tcase_add_test(tc, test_to_lower_str_null);
  tcase_add_test(tc, test_to_lower_empty_string);
  tcase_add_test(tc, test_to_lower_no_upper);
  tcase_add_test(tc, test_to_lower_with_upper);

  tcase_add_test(tc, test_s21_to_upper_normal);
  tcase_add_test(tc, test_s21_to_upper_mixed);
  tcase_add_test(tc, test_s21_to_upper_empty);
  suite_add_tcase(s, tc);
  return s;
}
