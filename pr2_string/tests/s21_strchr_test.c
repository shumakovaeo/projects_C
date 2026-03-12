
#include "string_test.h"

START_TEST(test_s21_strchr_found) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strchr(str, 'l'), strchr(str, 'l'));
}
END_TEST

START_TEST(test_s21_strchr_not_found) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
}
END_TEST

START_TEST(test_s21_strchr_null_term) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

Suite *suite_s21_strchr() {
  Suite *s = suite_create("s21_strchr");
  TCase *tc = tcase_create("s21_strchr");
  tcase_add_test(tc, test_s21_strchr_found);
  tcase_add_test(tc, test_s21_strchr_not_found);
  tcase_add_test(tc, test_s21_strchr_null_term);
  suite_add_tcase(s, tc);
  return s;
}
