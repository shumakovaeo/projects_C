
#include "string_test.h"

START_TEST(test_s21_strncmp_equal) {
  const char *str1 = "hello ";
  const char *str2 = "hello ";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

#include <stdio.h>

START_TEST(test_s21_strncmp_less) {
  const char *str1 = "abc ";
  const char *str2 = "abZ ";
  int s21_result = s21_strncmp(str1, str2, 3);
  int std_result = strncmp(str1, str2, 3);
  int s21_sign = s21_result > 0 ? 1 : (s21_result < 0 ? -1 : 0);
  int std_sign = std_result > 0 ? 1 : (std_result < 0 ? -1 : 0);
  ck_assert_int_eq(s21_sign, std_sign);
  // printf("s21: %d, std: %d\n", s21_result, std_result);
}
END_TEST

START_TEST(test_s21_strncmp_more) {
  const char *str1 = "abZ ";
  const char *str2 = "abc ";
  int s21_result = s21_strncmp(str1, str2, 3);
  int std_result = strncmp(str1, str2, 3);
  int s21_sign = s21_result > 0 ? 1 : (s21_result < 0 ? -1 : 0);
  int std_sign = std_result > 0 ? 1 : (std_result < 0 ? -1 : 0);
  ck_assert_int_eq(s21_sign, std_sign);
  // printf("s21: %d, std: %d\n", s21_result, std_result);
}
END_TEST

START_TEST(test_s21_strncmp_zero_n) {
  const char *str1 = "hello";
  const char *str2 = "world";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
}
END_TEST

Suite *suite_s21_strncmp() {
  Suite *s = suite_create("s21_strncmp");
  TCase *tc = tcase_create("s21_strncmp");
  tcase_add_test(tc, test_s21_strncmp_equal);
  tcase_add_test(tc, test_s21_strncmp_less);
  tcase_add_test(tc, test_s21_strncmp_more);
  tcase_add_test(tc, test_s21_strncmp_zero_n);
  suite_add_tcase(s, tc);
  return s;
}
