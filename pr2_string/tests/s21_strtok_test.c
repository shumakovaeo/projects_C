
#include "string_test.h"

START_TEST(test_s21_strtok_normal) {
  char str_s21[] = "hello world";
  char *res1 = s21_strtok(str_s21, " ");

  ck_assert_ptr_nonnull(res1);
  ck_assert_str_eq(res1, "hello");

  res1 = s21_strtok(NULL, " ");
  ck_assert_ptr_nonnull(res1);
  ck_assert_str_eq(res1, "world");

  res1 = s21_strtok(NULL, " ");
  ck_assert_ptr_eq(res1, NULL);

  ck_assert_str_eq(str_s21, "hello");
  char str_std[] = "hello world";
  char *res2 = strtok(str_std, " ");
  ck_assert_ptr_nonnull(res2);
  ck_assert_str_eq(res2, "hello");

  res2 = strtok(NULL, " ");
  ck_assert_ptr_nonnull(res2);
  ck_assert_str_eq(res2, "world");

  res2 = strtok(NULL, " ");
  ck_assert_ptr_eq(res2, NULL);
}
END_TEST

START_TEST(test_s21_strtok_no_delim) {
  char str1[] = "hello";
  char str2[] = "hello";
  const char *delim = " ";
  char *res1 = s21_strtok(str1, delim);
  char *res2 = strtok(str2, delim);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strtok_empty) {
  char str1[] = "";
  char str2[] = "";
  const char *delim = " ";
  char *res1 = s21_strtok(str1, delim);
  char *res2 = strtok(str2, delim);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

Suite *suite_s21_strtok() {
  Suite *s = suite_create("s21_strtok");
  TCase *tc = tcase_create("s21_strtok");
  tcase_add_test(tc, test_s21_strtok_normal);
  tcase_add_test(tc, test_s21_strtok_no_delim);
  tcase_add_test(tc, test_s21_strtok_empty);
  suite_add_tcase(s, tc);
  return s;
}
