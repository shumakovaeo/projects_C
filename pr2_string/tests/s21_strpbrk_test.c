
#include "string_test.h"

START_TEST(test_s21_strpbrk_found) {
  const char *str1 = "hello world";
  const char *str2 = "w";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_not_found) {
  const char *str1 = "hello";
  const char *str2 = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_str2) {
  const char *str1 = "hello";
  const char *str2 = "";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *suite_s21_strpbrk() {
  Suite *s = suite_create("s21_strpbrk");
  TCase *tc = tcase_create("s21_strpbrk");
  tcase_add_test(tc, test_s21_strpbrk_found);
  tcase_add_test(tc, test_s21_strpbrk_not_found);
  tcase_add_test(tc, test_s21_strpbrk_empty_str2);
  suite_add_tcase(s, tc);
  return s;
}
