
#include "string_test.h"

START_TEST(test_s21_strrchr_found) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
}
END_TEST

START_TEST(test_s21_strrchr_not_found) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_s21_strrchr_null_term) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

Suite *suite_s21_strrchr() {
  Suite *s = suite_create("s21_strrchr");
  TCase *tc = tcase_create("s21_strrchr");
  tcase_add_test(tc, test_s21_strrchr_found);
  tcase_add_test(tc, test_s21_strrchr_not_found);
  tcase_add_test(tc, test_s21_strrchr_null_term);
  suite_add_tcase(s, tc);
  return s;
}
