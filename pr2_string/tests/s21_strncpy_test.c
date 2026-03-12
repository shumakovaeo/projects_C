
#include "string_test.h"

START_TEST(test_s21_strncpy_normal) {
  char dest[10];
  const char *src = "hello";
  ck_assert_ptr_eq(s21_strncpy(dest, src, 6), strncpy(dest, src, 6));
  ck_assert_str_eq(dest, "hello");
}
END_TEST

START_TEST(test_s21_strncpy_shorter) {
  char dest[10];
  const char *src = "hi";
  ck_assert_ptr_eq(s21_strncpy(dest, src, 5), strncpy(dest, src, 5));
  ck_assert_str_eq(dest, "hi");
}
END_TEST

START_TEST(test_s21_strncpy_zero_n) {
  char dest[10] = "old";
  const char *src = "new";
  int num = 0;
  ck_assert_ptr_eq(s21_strncpy(dest, src, num), strncpy(dest, src, num));
  ck_assert_str_eq(dest, "old");
}
END_TEST

Suite *suite_s21_strncpy() {
  Suite *s = suite_create("s21_strncpy");
  TCase *tc = tcase_create("s21_strncpy");
  tcase_add_test(tc, test_s21_strncpy_normal);
  tcase_add_test(tc, test_s21_strncpy_shorter);
  tcase_add_test(tc, test_s21_strncpy_zero_n);
  suite_add_tcase(s, tc);
  return s;
}
