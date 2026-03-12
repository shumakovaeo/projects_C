
#include "string_test.h"

START_TEST(test_s21_memcpy_normal) {
  char dest[10];
  const char *src = "hello";
  ck_assert_ptr_eq(s21_memcpy(dest, src, 6), memcpy(dest, src, 6));
  ck_assert_str_eq(dest, "hello");
}
END_TEST

START_TEST(test_s21_memcpy_overlap) {
  char dest[10] = "hello";
  ck_assert_ptr_eq(s21_memcpy(dest + 2, dest, 3), memcpy(dest + 2, dest, 3));
  // Проверка на корректность (оригинал memcpy не безопасен для перекрытия, но
  // тест на равенство)
}
END_TEST

START_TEST(test_s21_memcpy_zero_n) {
  char dest[10] = "old";
  const char *src = "new";
  ck_assert_ptr_eq(s21_memcpy(dest, src, 0), memcpy(dest, src, 0));
  ck_assert_str_eq(dest, "old");
}
END_TEST

Suite *suite_s21_memcpy() {
  Suite *s = suite_create("s21_memcpy");
  TCase *tc = tcase_create("s21_memcpy");
  tcase_add_test(tc, test_s21_memcpy_normal);
  tcase_add_test(tc, test_s21_memcpy_overlap);
  tcase_add_test(tc, test_s21_memcpy_zero_n);
  suite_add_tcase(s, tc);
  return s;
}
