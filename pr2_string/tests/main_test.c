

#include "./main_test.h"

int main() {
  SRunner *sr = srunner_create(NULL);

  srunner_add_suite(sr, suite_s21_sprintf());
  srunner_add_suite(sr, suite_s21_sscanf());
  srunner_add_suite(sr, suite_s21_strlen());
  srunner_add_suite(sr, suite_s21_memchr());
  srunner_add_suite(sr, suite_s21_memcmp());
  srunner_add_suite(sr, suite_s21_memcpy());
  srunner_add_suite(sr, suite_s21_memset());
  srunner_add_suite(sr, suite_s21_strchr());
  srunner_add_suite(sr, suite_s21_strcspn());
  srunner_add_suite(sr, suite_s21_strerror());
  srunner_add_suite(sr, suite_s21_strncat());
  srunner_add_suite(sr, suite_s21_strncmp());
  srunner_add_suite(sr, suite_s21_strncpy());
  srunner_add_suite(sr, suite_s21_strpbrk());
  srunner_add_suite(sr, suite_s21_strrchr());
  srunner_add_suite(sr, suite_s21_strstr());
  srunner_add_suite(sr, suite_s21_strtok());
  srunner_add_suite(sr, suite_s21_to_upper());
  srunner_add_suite(sr, suite_s21_to_lower());
  srunner_add_suite(sr, suite_s21_insert());
  srunner_add_suite(sr, suite_s21_trim());

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
