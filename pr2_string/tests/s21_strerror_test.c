
#include "string_test.h"

START_TEST(test_s21_strerror_valid) {
  int errnum = 1;  // EINVAL или другой
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

START_TEST(test_s21_strerror_zero) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
}
END_TEST

START_TEST(test_s21_strerror_large) {
  int errnum = 1000;  // За пределами стандартных
  // Предполагаем, что ваша реализация обрабатывает как strerror
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

Suite *suite_s21_strerror() {
  Suite *s = suite_create("s21_strerror");
  TCase *tc = tcase_create("s21_strerror");
  tcase_add_test(tc, test_s21_strerror_valid);
  tcase_add_test(tc, test_s21_strerror_zero);
  tcase_add_test(tc, test_s21_strerror_large);
  suite_add_tcase(s, tc);
  return s;
}
