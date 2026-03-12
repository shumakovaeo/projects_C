
#include "string_test.h"

START_TEST(test_s21_memchr_found) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_memchr(str, 'l', 5), memchr(str, 'l', 5));
}
END_TEST

START_TEST(test_s21_memchr_not_found) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_memchr(str, 'z', 5), memchr(str, 'z', 5));
}
END_TEST

START_TEST(test_s21_memchr_zero_n) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_memchr(str, 'h', 0), memchr(str, 'h', 0));
}
END_TEST

Suite *suite_s21_memchr() {
  Suite *s = suite_create("s21_memchr");
  TCase *tc = tcase_create("s21_memchr");
  tcase_add_test(tc, test_s21_memchr_found);
  tcase_add_test(tc, test_s21_memchr_not_found);
  tcase_add_test(tc, test_s21_memchr_zero_n);
  suite_add_tcase(s, tc);
  return s;
}
