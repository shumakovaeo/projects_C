#include "tests.h"

Suite *s21_sute(void) {
  Suite *s = suite_create("S21_DECIMAL");
  return s;
}

int main(void) {
  SRunner *sr = srunner_create(s21_sute());

  srunner_add_suite(sr, s21_test_add());
  srunner_add_suite(sr, s21_test_sub());
  srunner_add_suite(sr, s21_test_mul());
  srunner_add_suite(sr, s21_test_div());

  srunner_add_suite(sr, s21_test_is_less());
  srunner_add_suite(sr, s21_test_is_less_or_equal());
  srunner_add_suite(sr, s21_test_is_greater());
  srunner_add_suite(sr, s21_test_is_greater_or_equal());
  srunner_add_suite(sr, s21_test_is_equal());
  srunner_add_suite(sr, s21_test_is_not_equal());

  srunner_add_suite(sr, s21_test_from_decimal_to_int());
  srunner_add_suite(sr, s21_test_from_int_to_decimal());
  srunner_add_suite(sr, s21_test_from_float_to_decimal());
  srunner_add_suite(sr, s21_test_from_decimal_to_float());

  srunner_add_suite(sr, s21_test_floor());
  srunner_add_suite(sr, s21_test_round());
  srunner_add_suite(sr, s21_test_truncate());
  srunner_add_suite(sr, s21_test_negate());

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
