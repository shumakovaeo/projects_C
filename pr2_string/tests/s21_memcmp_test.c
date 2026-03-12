
#include "string_test.h"

START_TEST(test_s21_memcmp_equal) {
  const char *str1 = "hello";
  const char *str2 = "hello";
  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
}
END_TEST

START_TEST(test_s21_memcmp_less) {
  const char *str1 = "abc";
  const char *str2 = "abd";
  ck_assert_int_eq(s21_memcmp(str1, str2, 3), memcmp(str1, str2, 3));
}
END_TEST

START_TEST(test_s21_memcmp_zero_n) {
  const char *str1 = "hello";
  const char *str2 = "world";
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

Suite *suite_s21_memcmp() {
  Suite *s = suite_create("s21_memcmp");
  TCase *tc = tcase_create("s21_memcmp");
  tcase_add_test(tc, test_s21_memcmp_equal);
  tcase_add_test(tc, test_s21_memcmp_less);
  tcase_add_test(tc, test_s21_memcmp_zero_n);
  suite_add_tcase(s, tc);
  return s;
}
