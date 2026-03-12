
#include "string_test.h"

START_TEST(test_s21_strncat_normal) {
  // Две копии dest для корректного сравнения
  char dest_s21[20] = "hello";
  char dest_std[20] = "hello";
  const char *src = " world";

  char *result_s21 = s21_strncat(dest_s21, src, 7);
  char *result_std = strncat(dest_std, src, 7);

  ck_assert_ptr_eq(result_s21, dest_s21);
  ck_assert_ptr_eq(result_std, dest_std);

  ck_assert_str_eq(dest_s21, dest_std);
  ck_assert_str_eq(
      dest_s21,
      "hello world");  // Дополнительная проверка на ожидаемый результат
}
END_TEST

START_TEST(test_s21_strncat_zero_n) {
  char dest_s21[20] = "hello";
  char dest_std[20] = "hello";
  const char *src = " world";

  char *result_s21 = s21_strncat(dest_s21, src, 0);
  char *result_std = strncat(dest_std, src, 0);

  ck_assert_ptr_eq(result_s21, dest_s21);
  ck_assert_ptr_eq(result_std, dest_std);

  ck_assert_str_eq(dest_s21, dest_std);
  ck_assert_str_eq(dest_s21, "hello");
}
END_TEST

START_TEST(test_s21_strncat_partial) {
  char dest_s21[20] = "hi";
  char dest_std[20] = "hi";
  const char *src = "hello";

  char *result_s21 = s21_strncat(dest_s21, src, 2);
  char *result_std = strncat(dest_std, src, 2);

  ck_assert_ptr_eq(result_s21, dest_s21);
  ck_assert_ptr_eq(result_std, dest_std);

  ck_assert_str_eq(dest_s21, dest_std);
  ck_assert_str_eq(dest_s21, "hihe");
}
END_TEST

Suite *suite_s21_strncat() {
  Suite *s = suite_create("s21_strncat");
  TCase *tc = tcase_create("s21_strncat");
  tcase_add_test(tc, test_s21_strncat_normal);
  tcase_add_test(tc, test_s21_strncat_zero_n);
  tcase_add_test(tc, test_s21_strncat_partial);
  suite_add_tcase(s, tc);
  return s;
}
