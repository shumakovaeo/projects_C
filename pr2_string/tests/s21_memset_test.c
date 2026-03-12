
#include "string_test.h"

START_TEST(test_s21_memset_normal) {
  char str[10] = "hello";
  ck_assert_ptr_eq(s21_memset(str, 'x', 5), memset(str, 'x', 5));
  ck_assert_str_eq(str, "xxxxx");
}
END_TEST

START_TEST(test_s21_memset_zero_n) {
  char str[10] = "hello";
  int num = 0;
  ck_assert_ptr_eq(s21_memset(str, 'x', num), memset(str, 'x', num));
  ck_assert_str_eq(str, "hello");
}
END_TEST

START_TEST(test_s21_memset_full) {
  char str[5];
  ck_assert_ptr_eq(s21_memset(str, 0, 5), memset(str, 0, 5));
  ck_assert_mem_eq(str, "\0\0\0\0\0", 5);
}
END_TEST

Suite *suite_s21_memset() {
  Suite *s = suite_create("s21_memset");
  TCase *tc = tcase_create("s21_memset");
  tcase_add_test(tc, test_s21_memset_normal);
  tcase_add_test(tc, test_s21_memset_zero_n);
  tcase_add_test(tc, test_s21_memset_full);
  suite_add_tcase(s, tc);
  return s;
}
